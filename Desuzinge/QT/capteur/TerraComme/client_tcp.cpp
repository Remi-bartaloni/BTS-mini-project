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
    struct sockaddr_in dest_addr;
    QMessageBox msgbox;

    if((sock = socket(AF_INET, SOCK_STREAM, 0)) !=- 1)
    {
        dest_addr.sin_family = AF_INET;
        dest_addr.sin_port = htons(port);
        dest_addr.sin_addr.s_addr = inet_addr(ip.c_str());

        memset(&(dest_addr.sin_zero), 0, 8);
        if(connect(sock, (struct sockaddr *)&dest_addr, sizeof(struct sockaddr)) == 0)
        {

        }
        else
        {
            msgbox.setText("connect erreur");
            msgbox.exec();
        }

    }
    else
    {
        msgbox.setText("sock erreur");
        msgbox.exec();
    }

}


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------


void Client_tcp::envoyer(string &rq2)
{
    int pos;
    string rq("GET /status.xml HTTP/1.1\r\nHost: \r\nUser-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64; rv:27.0) Gecko/20100101 Firefox/27.0\r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n\r\n");

    pos = rq.find_first_of(":");
    pos = pos + 2;
    rq.insert(pos,ip);


    pos = rq.find_first_of("l");
    pos = pos + 1;
    rq.insert(pos,rq2);

    write(sock, rq.c_str(), rq.size());
}


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------


string Client_tcp::recevoir()
{
    char bef;
    int pos;
    string bef2;

    string rq("GET /status.xml HTTP/1.1\r\nHost: \r\nUser-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64; rv:27.0) Gecko/20100101 Firefox/27.0\r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n\r\n");

    pos = rq.find_first_of(":");
    pos = pos + 2;
    rq.insert(pos,ip);

    write(sock, rq.c_str(), rq.size());

    while (read(sock, &bef, 1) == 1)
    {
        bef2.append(&bef,1);
    }

    return bef2;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

Client_tcp::~Client_tcp()
{
    ::close (sock);
}
