#ifndef PORT_SERIE_H
#define PORT_SERIE_H

#include <string>

using namespace std;

class Port_serie
{
    int fb_lcd;
    char ligne;
    char clear;
    char debut;

public:
    Port_serie();

    void envoyer(char *, int);
    void effacer();
    void debut_lcd();
    void ligne_suvent();

};

#endif // PORT_SERIE_H
