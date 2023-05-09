#include "port_serie.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <time.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <signal.h>


using namespace std;

Port_serie::Port_serie()
{
    ligne = 0x0A;
    clear = 0x0c;
    debut = 0x08;

    fb_lcd = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY);

    struct termios lcd;

    fcntl(fb_lcd, F_SETFL, 0);

    tcgetattr(fb_lcd, &lcd);
    cfsetispeed(&lcd, B9600);
    cfsetispeed(&lcd, B9600);

    lcd.c_cflag &= ~PARENB;
    lcd.c_cflag &= ~CSTOPB;
    lcd.c_cflag &= ~CSIZE;
    lcd.c_cflag |= CS8;
    lcd.c_cflag |= (CLOCAL | CREAD);
    tcsetattr(fb_lcd, TCSANOW, &lcd);

   // cout<<"teste1"<<endl;
}


void Port_serie::envoyer(char *bef, int taill)
{
    write (fb_lcd,bef,taill);
}

void Port_serie::effacer()
{
    write (fb_lcd,&clear,1);
}

void Port_serie::debut_lcd()
{
    write (fb_lcd,&debut,1);
}

void Port_serie::ligne_suvent()
{
    write (fb_lcd,&ligne,1);
}
