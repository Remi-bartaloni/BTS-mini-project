#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>


int main(int argc, char const *argv[])
{	
	int clientSocket;
	struct sockaddr_in serverAddr;
	char buffer[1024];

	if((clientSocket = socket(PF_INET, SOCK_STREAM, 0)) != -1)
	{
		printf("[+]Socket Creer.\n");

		bzero(&serverAddr, sizeof(serverAddr));
		serverAddr.sin_family = AF_INET;
		serverAddr.sin_port = htons(22);
		serverAddr.sin_addr.s_addr = inet_addr(argv[1]);

		if((connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr))) != -1)
		{
			printf("[+]Connecter au Server.\n");

			recv(clientSocket, buffer, 1024, 0);
			printf("%s\n", buffer);
		}
		else	perror("connect:");
		close(clientSocket);	
	}
	else	perror("socket:");
	exit (0);
}

