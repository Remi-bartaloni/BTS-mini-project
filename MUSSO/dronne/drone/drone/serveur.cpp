#include "serveur.h"

#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

Serveur::Serveur()
{
    struct sockaddr_in serverAddr;

    if((clientSocket = socket(PF_INET, SOCK_DGRAM, 0)) != -1)
    {
        bzero(&serverAddr, sizeof(serverAddr));
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(5556);
        serverAddr.sin_addr.s_addr = inet_addr("192.168.1.1");

        if((connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr))) != -1)
        {
            cout<<"- Connecter au Server."<<endl;
        }
        else	perror("connect:");
    }
    else	perror("socket:");
}

Serveur::~Serveur()
{
     ::close(clientSocket);
}
