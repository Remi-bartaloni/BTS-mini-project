#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <termios.h> 

	void config(int fb)
	{
		struct termios options;

		fcntl(fb, F_SETFL, 0);

     	tcgetattr(fb, &options);                                                      // lecture de la configuration du coupleur
     	cfsetispeed(&options, B9600);                                                     // 4800 bauds
     	cfsetospeed(&options, B9600);                                                     // 4800 bauds
      	options.c_cflag &= ~PARENB;                                                       // pas de aprité
      	options.c_cflag &= ~CSTOPB;                                                       // 1 bit de stop
      	options.c_cflag &= ~CSIZE;                                                        // 8 bits de données
      	options.c_cflag |= CS8;                                                           // 8 bits de données
      	options.c_cflag |= (CLOCAL | CREAD);
      	tcsetattr(fb, TCSANOW, &options);
	}

int main()
{
	int fb, c, i =0;
	char bef[1024];
	FILE *ft;

    if ((fb = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY)) == -1)                                                                       // si l'ouverture a echoué
    {
      perror("open_port: Unable to open /dev/ttyUSB0 - ");
      exit(1);
    }

    config(fb);

    if ((ft = fopen("test.txt","r")) == NULL)
   	{
   		perror("open_port: txt ");
   		exit(1);
  	 }

      while ( fgets ( bef, (sizeof (bef))+1, ft ) != NULL )
      {
      	printf("%s", bef);
        i = 0;
        do
        {
          i++;
        }
        while(bef[i] != '\0');
        //printf("%d\n", i);
        write (fb, bef, i);
      //  sleep(1);
      }   

    close (fb);
    fclose (ft);

	return 0;
}