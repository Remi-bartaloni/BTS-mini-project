#ifndef RADIO_H
#define RADIO_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <linux/i2c-dev.h>
#include <iostream>
#include <unistd.h>

using namespace std;

class Radio
{
	double freq;
	int i2c;
	
	public:
    
    	Radio(int);

    	void setradio(double);

    	void mute(double);

    	~Radio();


};

#endif