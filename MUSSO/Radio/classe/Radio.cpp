#include "Radio.h"

Radio::Radio(int arge)
{
	char fh;
	char fl;
	

	if(arge != 2)
	{
		cout<<"Il faut 2 argument"<<endl;
		exit (-1);
	}

	if ((i2c = open("/dev/i2c-1", 0666)) == -1)	perror("open_port: Unable to open /dev/i2c-1");
    else
    {
    	cout<<"Le port est ouver sur /dev/i2c-1"<<endl;
    	if(ioctl(i2c, I2C_SLAVE, 0x60)<0)	perror("I2C_SLAVE erreur");
		else
		{
			
		}
    }
}

void Radio::setradio(double freq)
{
	int fb;
	char commend[5];

	if(freq <= 87)
	{
		cout<<"La frequense va de 87.5 à 108"<<endl;
		exit (-2);
	}

	if(freq >= 108)
	{
		cout<<"La frequense va de 87.5 à 108"<<endl;
		exit (-2);
	}

	cout<<"La frequense et: "<<freq<<endl;

	fb = 4 * (freq * 1000000 + 225000) / 32768;
	
	commend[0] = fb >> 8;
	commend[1] = fb & 0xff;
	commend[2] = 0xb0;
	commend[3] = 0x10;
	commend[4] = 0x00;

	if(write(i2c, commend, 5) != 5)		perror("write 1 erreur");
}

void Radio::mute(double freq)
{
	char commend;

	commend = 0x80;
	if(write(i2c, &commend, 1) != 1)		perror("write 1 erreur");

	//sleep(5);

	//setradio(freq);
}


Radio::~Radio()
{
	close(i2c);
}