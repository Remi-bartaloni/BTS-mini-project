#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;


int main()
{
	int i = 1;
	int clientSocket;
	struct sockaddr_in serverAddr;
	char buffer[1024];

	if((clientSocket = socket(PF_INET, SOCK_DGRAM, 0)) != -1)
	{
		cout<<"- Socket Creer."<<endl;

		bzero(&serverAddr, sizeof(serverAddr));
		serverAddr.sin_family = AF_INET;
		serverAddr.sin_port = htons(5556);
		serverAddr.sin_addr.s_addr = inet_addr("192.168.1.1");

		if((connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr))) != -1)
		{
			cout<<"- Connecter au Server."<<endl;
			

			sprintf(buffer,"AT*REF=%d,290718208\r",i);

			cout<<buffer<<endl;

			if(sendto(clientSocket,buffer,strlen(buffer),0,(struct sockaddr *)&serverAddr,sizeof(serverAddr)) <0)
			{
				perror("sendto:");
			}
			sleep(5);
			i++;	

			while(i <= 199)
			{
				cout<<""<<endl;
				//cin >> buffer;
				
				sprintf(buffer,"AT*PCMD=%d,1,0,0,1065353216,0\r",i);
				cout<<buffer<<endl;
				if(sendto(clientSocket,buffer,strlen(buffer),0,(struct sockaddr *)&serverAddr,sizeof(serverAddr)) <0)
				{
					perror("sendto;");
				}
				usleep(50000);
				i++;
			}

			cout<<""<<endl;
			sprintf(buffer,"AT*REF=%d,290717696\r",i);

			cout<<buffer<<endl;
				if(sendto(clientSocket,buffer,strlen(buffer),0,(struct sockaddr *)&serverAddr,sizeof(serverAddr)) <0)
				{
					perror("sendto;");
				}
		}
		else	perror("connect:");

		close(clientSocket);	
	}
	else	perror("socket:");

	exit (0);
}