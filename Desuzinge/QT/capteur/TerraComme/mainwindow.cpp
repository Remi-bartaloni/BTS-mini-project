using namespace std;

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client_tcp.h"
#include "parser.h"
#include "mesures.h"
#include "port_serie.h"

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sstream>
#include <vector>

#include <QPlainTextEdit>
#include <QThread>
#include <QDateTime>


#define IP "172.16.1.28"
#define PORT 80


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QObject::connect(ui->Quitter,         SIGNAL(clicked()), qApp, SLOT(quit()));
    QObject::connect(ui->Led,             SIGNAL(clicked()), this, SLOT(Test_Led()));
    QObject::connect(ui->Ventilateur,     SIGNAL(clicked()), this, SLOT(Test_Ventilateur()));
    QObject::connect(ui->Aquisition,      SIGNAL(clicked()), this, SLOT(acquisition()));
    QObject::connect(ui->historique,      SIGNAL(clicked()), this, SLOT(affich_historique()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

 void MainWindow::test_thread()
 {/*
     th = new MyThread;
     connect(th, SIGNAL(acquerir()), this, SLOT(pourVoir()));
     th->start();*/
 }

 void MainWindow::pourVoir()
 {
     cout << "Je vois tout !!" << endl;
 }

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------


void MainWindow::Test_Led()
{
    Client_tcp *client;
    client = new Client_tcp(PORT, IP);
    static int flag = 0;

    if(flag == 0)
    {
        string rq2("?r2=1");
        client->envoyer(rq2);
        std::cout<<"Led on"<<std::endl;
        flag = 1;
    }
    else if(flag == 1)
    {
        string rq2("?r2=0");
        client->envoyer(rq2);
        std::cout<<"Led off"<<std::endl;
        flag = 0;
    }
    delete(client);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::Test_Ventilateur()
{
    Client_tcp *client;
    client = new Client_tcp(PORT, IP);
    static int flag = 2;

    if(flag == 2)
    {
        string rq2("?r1=1");
        client->envoyer(rq2);
        std::cout<<"Ventilateur on"<<std::endl;
        flag = 3;
    }
    else if(flag == 3)
    {
        string rq2("?r1=0");
        client->envoyer(rq2);
        std::cout<<"Ventilateur off"<<std::endl;
        flag = 2;
    }
    delete(client);
}


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------


void MainWindow::manuelle()
{
    int i;
    char te[] = "Temp: ";
    char hu[] = "Hume: ";
    char pp[] = " C";
    char bb[] = " %RH";

    Port_serie *port;
    port = new Port_serie;
    port->effacer();
    port->debut_lcd();

    string trame;

    Client_tcp *client;
    client = new Client_tcp(PORT, IP);
    trame = client->recevoir();

    //QString s(trame.c_str());
    //ui->plainTextEdit->setPlainText(s);

    Parser xml;
    Mesures mes = xml.extraire(trame);  

    ostringstream ss;
    ss << mes.get_temperature();
    string t(ss.str());

    QString temp(t.c_str());
    ui->Temp->setText(temp);

    i = t.size();
    port->envoyer(te,6);

    sprintf(te,"%s",t.c_str());
    port->envoyer(te,i);

    port->envoyer(pp,2);


    ostringstream hh;
    hh << mes.get_humidite();
    string h(hh.str());

    QString hum(h.c_str());
    ui->Humidity->setText(hum);

    port->ligne_suvent();
    port->envoyer(hu,6);

    i = h.size();
    sprintf(hu,"%s",h.c_str());
    port->envoyer(hu,i);

    port->envoyer(bb,4);


    delete(port);
    delete(client);
}


void MainWindow::acquisition()
{
    static int flag = 0;


    if(ui->Manuler->isChecked() == 1)
    {
        manuelle();
    }

    if(ui->Automatique->isChecked() == 1)
    {


        if(flag == 0)
        {
            flag = 1;
            cout<<"on"<<endl;
            thread = new MyThread;
            //connect(thread, SIGNAL(acquerir()), this, SLOT(manuelle()));
            connect(thread, SIGNAL(acquerir(Mesures)), this, SLOT(automatique(Mesures)));
            thread->start();
            ui->Aquisition->setText("stop");
            ui->Manuler->hide();
        }
        else
        {
            flag = 0;
            ui->Aquisition->setText("Aquisition");
            ui->Manuler->show();
            cout<<"off"<<endl;
            thread->stop();
            thread->wait();
            delete(thread);
        }
    }

    //delete(thread);
}

void MainWindow::automatique(Mesures x)
{
    int i;
    char te[] = "Temp: ";
    char hu[] = "Hume: ";
    char pp[] = " C";
    char bb[] = " %RH";

    Port_serie *port;
    port = new Port_serie;
    port->effacer();
    port->debut_lcd();

    conteneur.push_back(x);

    ostringstream ss;
    ss << x.get_temperature();
    string t(ss.str());

    QString temp(t.c_str());
    ui->Temp->setText(temp);

    i = t.size();
    port->envoyer(te,6);

    sprintf(te,"%s",t.c_str());
    port->envoyer(te,i);

    port->envoyer(pp,2);


    ostringstream hh;
    hh << x.get_humidite();
    string h(hh.str());


    QString hum(h.c_str());
    ui->Humidity->setText(hum);

    port->ligne_suvent();
    port->envoyer(hu,6);

    i = h.size();
    sprintf(hu,"%s",h.c_str());
    port->envoyer(hu,i);

    port->envoyer(bb,4);


    delete(port);
}


void MainWindow::affich_historique()
{
    size_t i = 0;
    char bef[60];
    string histo;
    char temp[7], hum[7], date[60];

    bef[0] = 0;

    while(i < conteneur.size())
    {
        Mesures mesure = conteneur[i];
        ++i;

        sprintf(temp,"%.2f",mesure.get_temperature());

        sprintf(hum,"%.2f",mesure.get_humidite());

        QDateTime dt = mesure.get_date();
        QString qs = dt.toString("dddd dd hh:mm");

        sprintf(date,"%s",qs.toStdString().c_str());

        sprintf(bef, "Date:%s     temp = %s°c      hum = %s RH\n", date, temp, hum);

        histo.insert(0,bef);
    }

    QString historique(histo.c_str());
    ui->plainTextEdit->setPlainText(historique);
}
