#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
	int sock_serv;
	struct sockaddr_in serveur;

	int newclien;
	struct sockaddr_in clien;

	socklen_t addr_size;

	if((sock_serv = socket(AF_INET, SOCK_STREAM, 0)) != -1)
	{
		printf("[+]Server Socket Creer.\n");

		bzero(&serveur, sizeof(serveur));
		serveur.sin_family = AF_INET;
		serveur.sin_port = htons(22);
		serveur.sin_addr.s_addr = inet_addr(argv[1]);

		if((bind(sock_serv, (struct sockaddr*)&serveur, sizeof(serveur))) != -1)
		{
			printf("[+]Bind au Port 22.\n");

			listen(sock_serv, 5);
			printf("[+]listen...\n");

			newclien = accept(sock_serv, (struct sockaddr*)&clien, &addr_size);
			send(newclien, "Salut", strlen("Salut"), 0);
		}
		else	perror("bind:");
		close(newclien);
		close(sock_serv);	
	}
	else	perror("socket:");
	exit (0);
}