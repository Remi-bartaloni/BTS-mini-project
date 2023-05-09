#include "mythread.h"
#include "mesures.h"
#include "parser.h"
#include "client_tcp.h"

#include <iostream>
//#include

#define IP "172.16.1.28"
#define PORT 80

using namespace std;

MyThread::MyThread(QObject *parent) :
    QThread(parent)
{
    is_running = true;
    qRegisterMetaType< Mesures >();
}

void MyThread::run()
{
    while(is_running == true)
    {
        //emit(acquerir(17));
        automatique();
        cout<<"a"<<endl;
        QThread::msleep(1000);
    }
}

void MyThread::stop()
{
    is_running = false;
}


void MyThread::automatique()
{
    string trame;

    Client_tcp *client;
    client = new Client_tcp(PORT, IP);
    trame = client->recevoir();

    Parser xml;
    Mesures mes = xml.extraire(trame);

    emit(acquerir(mes));

    delete(client);
}
