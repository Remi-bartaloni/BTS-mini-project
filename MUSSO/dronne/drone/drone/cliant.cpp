using namespace std;

#include "cliant.h"

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

cliant::cliant()
{


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
        }
        else	perror("connect:");

        close(clientSocket);
    }
    else	perror("socket:");
}


cliant::envoier(char &bef)
{
    sprintf(buffer,"%s\r",bef);

    cout<<buffer<<endl;

    if(sendto(clientSocket,buffer,strlen(buffer),0,(struct sockaddr *)&serverAddr,sizeof(serverAddr)) <0)
    {
        perror("sendto:");
    }
}
