#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <linux/i2c-dev.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	int i2c;
	char commend[5];
	int fb;
	char fh;
	char fl;
	double freq;

	if(argc != 3)
	{
		printf("Il faut 3 argument\n");
		exit (-1);
	}

	if ((i2c = open(argv[1], 0666)) == -1)	perror("open_port: Unable to open /dev/i2c-1");
    else
    {
    	printf("Le port est ouver sur %s\n", argv[1]);
    	if(ioctl(i2c, I2C_SLAVE, 0x60)<0)	perror("I2C_SLAVE erreur");
		else
		{
			freq = atof(argv[2]);
			if(freq <= 87)
			{
				printf("La frequense va de 87.5 à 108\n");
				exit (-2);
			}

			if(freq >= 108)
			{
				printf("La frequense va de 87.5 à 108\n");
				exit (-2);
			}

			printf("La frequense et %f\n", freq);

			fb = 4 * (freq * 1000000 + 225000) / 32768;
			
			commend[0] = fb >> 8;
			commend[1] = fb & 0xff;
			commend[2] = 0xb0;
			commend[3] = 0x10;
			commend[4] = 0x00;

			if(write(i2c, commend, 5) != 5)	perror("write 1 erreur");
		}
    }
    close(i2c);
	exit (0);
}