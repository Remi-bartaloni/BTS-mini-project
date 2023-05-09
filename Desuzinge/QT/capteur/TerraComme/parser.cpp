#include "parser.h"
#include "mesures.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>
#include <string.h>
#include <sstream>
#include <sys/types.h>
#include <unistd.h>
#include <QDateTime>
using namespace std;

Parser::Parser()
{

}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------


Mesures Parser::extraire(string &trame)
{

    float temp;
    float bef, bef2, humidite;
    string temp1("<Temperature1>");
    string temp2("<Temperature2>");

    int pos = trame.find(temp1);

    pos = pos + temp1.size();
    temp1 = trame.substr(pos, 4);


    pos = trame.find(temp2);

    pos = pos + temp2.size();
    temp2 = trame.substr(pos, 4);

    //cout<<temp1<<endl;
    //cout<<temp2<<endl;

    stringstream beff(temp1);
    beff >> bef;

    stringstream beff2(temp2);
    beff2 >> bef2;

    //cout<<bef<<endl;
    //cout<<bef2<<endl;

    temp = (bef2 + bef) / 2;



//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

    string humid("<Humidity2>");

    pos = trame.find(humid);

    pos = pos + humid.size();
    humid = trame.substr(pos, 4);

    stringstream h(humid);
    h >> humidite;

    QDateTime date = QDateTime::currentDateTime();

    Mesures mes(humidite, temp, date);

    return (mes);
}
