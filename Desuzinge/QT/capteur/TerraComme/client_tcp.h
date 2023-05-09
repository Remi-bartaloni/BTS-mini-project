#ifndef CLIENT_TCP_H
#define CLIENT_TCP_H

#include <string>
#include <QMessageBox>
using namespace std;

class Client_tcp
{
        int sock;
        short port;
        string ip;

    public:
        Client_tcp(short port, string ip);

        void envoyer(string&);

        string recevoir();

        ~Client_tcp();
};

#endif // CLIENT_TCP_H
