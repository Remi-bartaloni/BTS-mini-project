#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <time.h>



struct resultat{
  char decimal[4];
  char hexa[3];
  char bin[9];
};

//----------------------------------------------------------------------------------------------------

void menu()
{
  
  printf ("**************************************\n");
  printf ("* Affichage de l'heure.              *\n");
  printf ("* Convertion d'une valeur entiere.   *\n");
  printf ("**************************************\n");
  
  printf ("c - convertir une donnee.\n");
  printf ("q - sortir du programme.\n");
}

//----------------------------------------------------------------------------------------------------


void covert(struct resultat *result)
{
  int i = 7, tmp;
  int mask = 0x01;
  int choix;
    
  printf ("Chifre a convertir: ");
  scanf ("%d", &choix);
  while (getchar() != '\n');	//vider le beffer du claver
  printf ("\n");
  
  
  sprintf (result->decimal,"%d",choix);
  sprintf (result->hexa   ,"%.2X",choix);
  
  do
  {
      tmp = choix & mask;
      
      if (tmp)	result->bin[i] = '1';
      else 	result->bin[i] = '0';
      
      mask = mask << 1;
      i--;
  }
  while (i >= 0);
  result->bin[8] = '\0';
  

  printf ("Decimal:     %s\n"  , result->decimal);
  printf ("Hexadecimal: 0X%s\n", result->hexa);
  printf ("Binaire:     %s\n"  , result->bin);
  printf ("\n");   
}

//----------------------------------------------------------------------------------------------------

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

//----------------------------------------------------------------------------------------------------

void afiche(int fb_lcd, struct resultat *result)
{
  char ligne = 0x0A, clear = 0x0c, debut = 0x08;
      
  //printf ("%d:%d:%d\n", result->hour, result->min, result->sec);
  
  write (fb_lcd,&clear,1);
  write (fb_lcd,&debut,1);
  
  
  
  write (fb_lcd,&ligne,1);
  write (fb_lcd,"decimal: ",9);
  write (fb_lcd,result->decimal,strlen(result->decimal));
  
  write (fb_lcd,&ligne,1);
  write (fb_lcd,"hexa:    0X",11);
  write (fb_lcd,result->hexa,strlen(result->hexa));  
  
  write (fb_lcd,&ligne,1);
  write (fb_lcd,"bin:     b",10);
  write (fb_lcd,result->bin,strlen(result->bin));
  
}

//----------------------------------------------------------------------------------------------------

int fils (int fb_lcd,int pipe_fd[2])
{
  time_t t;
  char bef1[9] = {""}, cmde_curseur[] = {254,71,0,1};
  char bef = 'a', clear = 0x0C;
  
   struct tm *heure;
  
  while (bef != 'q')
  { 
    read(pipe_fd[0],&bef,1);
    
    t = time(NULL);
    heure = localtime(&t);
    
    sprintf (bef1   ,"%.2d:%.2d:%.2d", heure->tm_hour, heure->tm_min, heure->tm_sec);
    write (fb_lcd,cmde_curseur, 4);
    write (fb_lcd, bef1, strlen(bef1));
    
    sleep(1);
  }
  close (pipe_fd[0]);
  write (fb_lcd,&clear,1);
  
  exit (0);
}

//----------------------------------------------------------------------------------------------------

int main (int argc, char **argv)
{
  char choix = '\0', clear = 0x0C, debut = 0x08, choi_q = 'q';
  int fb_lcd, pid, fb;
  int pipe_fd[2];
  char bef2[4];
  struct resultat result;
  
  
  int mk, fifo, i;
  
  for (i = 0; i < argc; i++); //printf ("a%da\n", i);
    
  

  if(i != 3)
  {
    printf("il faux 2 argument\n");
    return -1;
  }  
  
  fifo = open ("lcd_mkfifo", O_WRONLY);
  if (fifo == -1)
  {
    perror("mkfifo");
    return -1;
  }
  


  write (fifo, argv[1], strlen(argv[1]));
  write (fifo, argv[2], strlen(argv[2]));
  unlink("lcd_mkfifo");
  close(fifo);
  
  printf("conexion\n");
  sleep (2);
  
  
  fb = open ("iden_mkfifo", O_RDONLY);
  if (fb == -1)
  {
    perror("fb");
    return -1;
  }
    
    read (fb, bef2, 3);
    bef2[3] = '\0';
    printf ("%s\n", bef2);
  
  close(fb);
    //printf("%d\n",(int)t)

  if (strcmp(bef2, "oui") == 0)
  {
    fb_lcd = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY);
	  
	  starte_por (fb_lcd);

	  if (fb_lcd == -1)
      {
	perror("open_port: Unable to open /dev/ttyS0");
      }
      
      write (fb_lcd,&clear,1);
      write (fb_lcd,&debut,1);
      
      if (pipe2(pipe_fd,O_NONBLOCK) == -1) printf("Erreur");
      
      pid = fork();
    
      switch (pid)
    {
      case -1: printf ("erreur\n");
      break;
      
      case 0:
	
	fils(fb_lcd, pipe_fd);
    
	//printf("%d:%d \n", heure->tm_hour, heure->tm_min);
	
	exit(0);
	
      break;
      
      default :
	
    
	while (1)
	{
	    menu();
	  
	    printf ("\n");
	    printf ("       Votre choix: ");
	    scanf ("%c", &choix);
	    while (getchar() != '\n');	//vider le beffer du claver
	    printf ("\n");
    
	    if (choix == 'c')		covert(&result);
      
    
	    else if (choix == 'q')	
	    {
	      write (pipe_fd[1], &choi_q,1);
	      close (pipe_fd[1]);
	      //sleep (2);
	      //write (fb_lcd,&clear,1);
	      return 0;
	    }
	    
	    else			printf("Valeur incoreccte\n\n");
      
	    afiche(fb_lcd, &result);

      
	}
    }
  }
  
  exit(0);
}