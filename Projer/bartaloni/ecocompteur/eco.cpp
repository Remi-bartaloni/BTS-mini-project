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
	string evoi = "GET /data.json HTTP/1.1\r\n";
	string tram;
	string conso_base = "conso_base";
	string conso_hc = "conso_hc";
	string conso_hp = "conso_hp";

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
					while(read(clientSocket, &buffer, 1) == 1)
					{
						tram.append(&buffer,1);
					}
					
					//printf("%s", tram.c_str());
					//printf("\n\n");

					position = tram.find(conso_base);
	    			position = position + conso_base.size() + 4;
	    			conso_base = tram.substr(position, 1);


					position = tram.find(conso_hc);
	    			position = position + conso_hc.size() + 6;
	    			conso_hc = tram.substr(position, 9);


	    			position = tram.find(conso_hp);
	    			position = position + conso_hp.size() + 6;
	    			conso_hp = tram.substr(position, 9);

	    			printf("Conso_base = %s\n", conso_base.c_str());
	    			printf("Conso_hc = %s\n", conso_hc.c_str());
	    			printf("Conso_hp = %s\n", conso_hp.c_str());
	    			printf("\n\n");
				}
			}
			else	perror("connect:");
			close(clientSocket);	
		}
		else	perror("socket:");
	exit (0);
}
