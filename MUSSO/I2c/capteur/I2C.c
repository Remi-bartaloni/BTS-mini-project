#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <linux/i2c-dev.h>
#include <unistd.h>

int main()
{
	int i2c;
	unsigned char commend[5];
	unsigned char version = 0;
	unsigned char lum = 0;
	unsigned char distance = 0;
	unsigned char distance1 = 0;
	unsigned char distance2 = 0;

	if ((i2c = open("/dev/i2c-1", 0666)) == -1)
    {
    	perror("open_port: Unable to open /dev/i2c-1");
    	exit(-1);
    }

	if(ioctl(i2c, I2C_SLAVE, 0x70)<0)
	{
		perror("I2C_SLAVE erreur");
		exit(-2);
	}

	commend[0] = 0x00;
	if(write(i2c, commend, 1) != 1)
	{
		perror("write 1 erreur");
		exit(-3);
	}


	if(read(i2c, &version, 1) != 1)
	{
		perror("read erreur");
		exit(-4);
	}

	printf("Vertion du capteur: %d\n", version);

	commend[0] = 0x00;
	commend[1] = 0x51;
	if(write(i2c, commend, 2) != 2)
	{
		perror("write 2 erreur");
		exit(-5);
	}

	sleep (1);
	commend[0] = 0x01;
	if(write(i2c, commend, 1) != 1)
	{
		perror("write 3 erreur");
		exit(-7);
	}

	if(read(i2c, &lum, 1) != 1)
	{
		perror("read 4 erreur");
		exit(-8);
	}

	printf("Lectur de la lumier %d\n", lum);

	sleep(1);

	commend[0] = 0x02;
	if(write(i2c, commend, 1) != 1)
	{
		perror("write 5 erreur");
		exit(-10);
	}

	if(read(i2c, &distance1, 1) != 1)
	{
		perror("read 1 erreur");
		exit(-11);
	}

	commend[0] = 0x03;
	if(write(i2c, commend, 1) != 1)
	{
		perror("write 7 erreur");
		exit(-13);
	}

	if(read(i2c, &distance2, 1) != 1)
	{
		perror("read 2 erreur");
		exit(-14);
	}

	distance = distance2 + (distance1 << 8);
	printf("Lectur de la distence %d\n", distance);
    close(i2c);
	return 0;
}