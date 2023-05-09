#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>

struct gps
{
	char GGA[100];
	char GGL[100];
	char GSL[100];
	char GSV[100];
	char VTG[100];
	char RMC[100];
};

struct decod
{
	char temp[15];
	char Heur[3];
	char min[3];
	char sec[3];

	char Latitude[100];
	char Latitude_deg[100];
	char Latitude_chif[100];
	char Latitude_orientation[100];

	char Longitude[100];
	char Longitude_deg[100];
	char Longitude_chif[100];
	char Longitude_orientation[100];

	char Altitude[100];
};

void starte_por (int fb)
{
	struct termios options_gps;

	fcntl(fb, F_SETFL, 0);

    tcgetattr(fb, &options_gps);                                                      // lecture de la configuration du coupleur
    cfsetispeed(&options_gps, B9600);                                                     // 9600 bauds
    cfsetispeed(&options_gps, B9600);

    options_gps.c_cflag &= ~PARENB;                                                       // pas de parité
    options_gps.c_cflag &= ~CSTOPB;                                                       // 1 bit de stop
    options_gps.c_cflag &= ~CSIZE;                                                        // 8 bits de données
    options_gps.c_cflag |= CS8;                                                           // 8 bits de données
    options_gps.c_cflag |= (CLOCAL | CREAD);
    tcsetattr(fb, TCSANOW, &options_gps);                                             // enregistrement de la configuration du coupleur
}

void main ()
{
	int fd_gps, fb_lcd, i = 0;
	char bef = 'a', tram[100], cmde_curseur[] = {254,71,0,1};
	struct gps strc_tram;
	struct decod dec_tram;
	char clear = 0x0C, ligne = 0x0A;



	fd_gps = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY);

	starte_por (fd_gps);

	if (fd_gps == -1)
    {
      perror("open_port: Unable to open /dev/ttyUSB0 ");
    }




    fb_lcd = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY);
	
	starte_por (fb_lcd);

	if (fb_lcd == -1)
    {
      perror("open_port: Unable to open /dev/ttyS0");
    }

    while(1)
    {
    	while (bef != '$') 
    	{
    		read(fd_gps,&bef,1);
    		i = 0;
    	}

    	do
    	{
    		read(fd_gps,&bef,1);
    		tram[i] = bef;
    		i++;
    	}
    	while (bef != '*');    		

    	
    	tram[i] = '\0';


    	if (strncmp("GPGGA",tram,5) == 0)  
    		{
    			printf("%s\n",strc_tram.GGA);
    			write (fb_lcd, &clear, 1);

    			strcpy(strc_tram.GGA, tram);

    			strncpy(dec_tram.Heur,strc_tram.GGA + 6 ,2);
    			dec_tram.Heur[2] = '\0';

 			   	strncpy(dec_tram.min,strc_tram.GGA + 8 ,2);
    			dec_tram.min[2] = '\0';

		    	strncpy(dec_tram.sec,strc_tram.GGA + 10 ,2);
    			dec_tram.sec[2] = '\0';

    			sprintf (dec_tram.temp,"%s:%s:%s UTC",dec_tram.Heur, dec_tram.min, dec_tram.sec);
    			
    			printf("%s\n",dec_tram.temp);

    			write (fb_lcd,cmde_curseur, 4);
    			write (fb_lcd, dec_tram.temp, strlen(dec_tram.temp));

    			

    			write (fb_lcd, &ligne, 1);



    			strncpy(dec_tram.Latitude_deg,strc_tram.GGA + 13 ,2);
    			dec_tram.Latitude_deg[2] = '\0';

    			strncpy(dec_tram.Latitude_chif,strc_tram.GGA + 15 ,11);
    			dec_tram.Latitude_chif[12] = '\0';

    			strncpy(dec_tram.Latitude_orientation,strc_tram.GGA + 27 ,1);
    			dec_tram.Latitude_orientation[1] = '\0';

    			sprintf (dec_tram.Latitude,"%s'%s'%s",dec_tram.Latitude_deg, dec_tram.Latitude_chif, dec_tram.Latitude_orientation);

    			write (fb_lcd, dec_tram.Latitude, strlen(dec_tram.Latitude));
    			printf("%s\n",dec_tram.Latitude);


    			write (fb_lcd, &ligne, 1);



    			strncpy(dec_tram.Longitude_deg,strc_tram.GGA + 30 ,3);
    			dec_tram.Longitude_deg[3] = '\0';

    			strncpy(dec_tram.Longitude_chif,strc_tram.GGA + 33 ,6);
    			dec_tram.Longitude_chif[7] = '\0';

    			strncpy(dec_tram.Longitude_orientation,strc_tram.GGA + 40 ,1);
    			dec_tram.Longitude_orientation[1] = '\0';

    			sprintf (dec_tram.Longitude,"%s'%s'%s",dec_tram.Longitude_deg, dec_tram.Longitude_chif, dec_tram.Longitude_orientation);

    			write (fb_lcd, dec_tram.Longitude, strlen(dec_tram.Longitude));
    			printf("%s\n",dec_tram.Longitude);



    			write (fb_lcd, &ligne, 1);



    			strncpy(dec_tram.Altitude,strc_tram.GGA + 51 ,6);
    			dec_tram.Altitude[6] = '\0';

    			sprintf (dec_tram.Longitude,"%s",dec_tram.Altitude);

    			write (fb_lcd, dec_tram.Altitude, strlen(dec_tram.Altitude));
    			printf("%s\n",dec_tram.Altitude);



    		}
    	if (strncmp(tram, "GPGLL", sizeof("GPGLL")-1) == 0)  
    		{
    			strcpy(strc_tram.GGL, tram);
    		}
    	if (strncmp(tram, "GPGSA", sizeof("GPGSA")-1) == 0)  
    		{
    			strcpy(strc_tram.GSL, tram);
    		}
    	if (strncmp(tram, "GPGSV", sizeof("GPGSV")-1) == 0)  
    		{
    			strcpy(strc_tram.GSV, tram);
    		}
    	if (strncmp(tram, "GPVTG", sizeof("GPVTG")-1) == 0)  
    		{
    			strcpy(strc_tram.VTG, tram);
    		}
    	if (strncmp(tram, "GPRMC", sizeof("GPRMC")-1) == 0)  
    		{
    			strcpy(strc_tram.RMC, tram);
			}

    	//printf("%s\n",strc_tram.GGA);
    	//write(fb_lcd,strc_tram.GGA,strlen(strc_tram.GGA));

    	
    	
    	//printf("%s UTC\n",dec_tram.Heur);

    }
}