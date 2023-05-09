#include "client_tcp.h"

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

Client_tcp::Client_tcp(short port, string ip):port(port), ip(ip)
{
    struct sockaddr_in serverAddr;

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

        }
        else
        {
            cout<<"connect erreur"<<endl;
        }

    }
    else
    {
        cout<<"sock erreur"<<endl;
    }

}


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------


void Client_tcp::envoyer(string &rq)
{
    write(clientSocket, rq.c_str(), rq.size());
}


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------


void Client_tcp::recevoir(string &tram)
{
    char bef;

    while (read(clientSocket, &bef, 1) == 1)
    {
        tram.append(&bef, 1);
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

Client_tcp::~Client_tcp()
{
    ::close (clientSocket);
}
