#ifndef CLIANT_H
#define CLIANT_H

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>


class cliant
{
    int clientSocket;
    struct sockaddr_in serverAddr;

public:
    cliant();

    void envoier(char&);
};

#endif // CLIANT_H
