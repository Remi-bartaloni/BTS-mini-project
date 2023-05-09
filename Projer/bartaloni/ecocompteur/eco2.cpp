#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <string>


using namespace std;



int main()
{
	string evoi = "GET /inst.json HTTP/1.1\r\n";
	string tram;
	string Date_Time = "Date_Time";

	int position = 0;

	int clientSocket;
	struct sockaddr_in serverAddr;
	char buffer;

		if((clientSocket = socket(PF_INET, SOCK_STREAM, 0)) != -1)
		{
			printf("[+]Socket Creer.\n");

			bzero(&serverAddr, sizeof(serverAddr));
			serverAddr.sin_family = AF_INET;
			serverAddr.sin_port = htons(80);
			serverAddr.sin_addr.s_addr = inet_addr("172.16.5.12");

			if((connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr))) != -1)
			{
				printf("[+]Connecter au Server.\n");

				if (write(clientSocket, evoi.c_str(), evoi.size()))
				{	
					printf("\n\n");
					if (write(clientSocket, evoi.c_str(), evoi.size()))
		            {   
		                printf("\n\n");
		                while(read(clientSocket, &buffer, 1) == 1)
		                {
		                    tram.append(&buffer,1);
		                }
		                
		                //printf("%s", tram.c_str());
		                //printf("\n\n");

		                position = tram.find(Date_Time);
		                position = position + Date_Time.size() + 2;
		                Date_Time = tram.substr(position, 10);

		                printf("Date_Time = %s\n", Date_Time.c_str());
		                printf("\n\n");
		            }
		        }
			}
			else	perror("connect:");
			close(clientSocket);	
		}
		else	perror("socket:");
	exit (0);
}
