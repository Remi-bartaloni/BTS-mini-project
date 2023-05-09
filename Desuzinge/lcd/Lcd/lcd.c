#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

char choix_quit = 'a';

struct resultat{
  char decimal[4];
  char hexa[3];
  char bin[9];
};
//----------------------------------------------------------------------------------------------------

/*void handler(int signal) 
{
  char t = 0x0D;
  int retour;
  
  if (signal == SIGINT)
  {
     choix_quit = 'q';
     retour = fclose(stdin);
     if(retour != 0)
       perror("fclose");
    //fwrite(&t, 1, 1, stdin);
    //printf("\nplus\n");
   
  }
}*/

void sighandler(int sig) 
{
  char t = 0x0D;
  int retour;
  
  signal(sig,sighandler);
  if (sig == SIGINT)
  {
     choix_quit = 'q';
     retour = fclose(stdin);
     if(retour != 0)
       perror("fclose");
    //fwrite(&t, 1, 1, stdin);
    //printf("\nplus\n");
   
  }
}



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


void covert(struct resultat *result, char *data)
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
  
  strcpy(data,result->decimal);
  strcpy(data+5,result->hexa);
  strcpy(data+10,result->bin);
  
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

void afiche(int fb_lcd, struct resultat *result, struct sembuf *operation, int semid)
{
  char ligne = 0x0A, clear = 0x0c, debut = 0x08;
      
  //printf ("%d:%d:%d\n", result->hour, result->min, result->sec);
  
  operation->sem_op = -1;			//demande le sémaphore
  semop(semid, operation, 1);
  
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
  
  operation->sem_op = 1;			//libère le sémaphore
  semop(semid, operation, 1);		//applique le sémaphore
  
}

//----------------------------------------------------------------------------------------------------

int fils (int fb_lcd,int pipe_fd[2], struct sembuf *operation, int semid)
{
  time_t t;
  char bef1[9] = {""}, cmde_curseur[] = {254,71,0,1};
  char bef = 'a', clear = 0x0C;
  int i;
  
   struct tm *heure;
  
  while (bef != 'q')
  { 
    operation->sem_op = -1;			//demande le sémaphore
    semop(semid, operation, 1);		//applique le sémaphore
    
    read(pipe_fd[0],&bef,1);
    
    t = time(NULL);
    heure = localtime(&t);
    
    sprintf (bef1   ,"%.2d:%.2d:%.2d", heure->tm_hour, heure->tm_min, heure->tm_sec);
    write (fb_lcd,cmde_curseur, 4);
    //write (fb_lcd, bef1, strlen(bef1));
    i =-1;
    do
    {
      i++;
      write (fb_lcd, &bef1[i], 1);
      usleep(90000);
    }
    while (i != (strlen(bef1)-1));
    
    operation->sem_op = 1;			//libère le sémaphore
    semop (semid, operation, 1);
    
    sleep(1);
  }
  close (pipe_fd[0]);
  write (fb_lcd,&clear,1);
  
  exit (0);
}

//----------------------------------------------------------------------------------------------------

int main (int argc, char **argv)
{
  char clear = 0x0C, debut = 0x08, choi_q = 'q', r;
  int fb_lcd, pid, fb, y, quite;
  int pipe_fd[2];
  char bef[80], bef2[10];
  struct resultat result;
  int mk, fifo, i, semid;
  key_t key;
  int shmid;
  char *data, *save;
  struct sembuf operation;
  //struct sigaction new_action, old_action;
  
  /*new_action.sa_handler = handler;
  sigemptyset(&new_action.sa_mask);
  new_action.sa_flags = 0;
  sigaction(SIGINT,&new_action,& old_action);
  */
  signal(SIGINT,sighandler);
  //printf("shm_size = %d\n",getpagesize());
  key = ftok("lcd.c",'R');
  
  shmid = shmget(key, getpagesize(), 0644);
  if (shmid == -1)
  {
    perror("shmid");
    return -1;
  }
  
  save = data = (char *)shmat(shmid,NULL, 0);
  if (save == "-1")
  {
    perror("save");
    return -1;
  }

  if(argc != 3)
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

  write (fifo, argv[1], strlen(argv[1])+1);
  write (fifo, argv[2], strlen(argv[2])+1);
  //unlink("lcd_mkfifo");
  
  
  //printf("conexion\n");
  //sleep (2);
  
  fb = open ("iden_mkfifo", O_RDONLY);
  if (fb == -1)
  {
    perror("fb");
    return -1;
  }
  
  quite = open ("quite", O_WRONLY | O_NONBLOCK);
  if (quite == -1)
  {
    perror("quite");
    return -1;
  }
  
  y = -1;
  do
  { 
     y++;
    read (fb, &bef2[y], 1);
  }
  while (bef2[y] != '\0');
    //printf ("%s\n", bef2);
  
  close(fb);
    //printf("%d\n",(int)t)

  if (strcmp(bef2, "oui") == 0)
  {
    fb_lcd = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY);
    starte_por (fb_lcd);
    if (fb_lcd == -1)
    {
	perror("open_port: Unable to open /dev/ttyS0");
	exit(-1);
    }
      
    write (fb_lcd,&clear,1);
    write (fb_lcd,&debut,1);
      
    if (pipe2(pipe_fd,O_NONBLOCK) == -1)
    {
      perror("Erreur");
      exit(-2);
    }
    
    //------------------------------------------------------------------------------------------------------------------------------------------------
    semid = semget(key, 1, IPC_CREAT | 0600);	//création du sémaphore
    semctl(semid, 0, SETVAL, 1);			//sémaphore 0
    operation.sem_num = 0;			//sémaphore 0
    operation.sem_flg = 0;			//On s'en occupe pas
    //------------------------------------------------------------------------------------------------------------------------------------------------
    pid = fork();
    
    switch (pid)
    {
      case -1: printf ("erreur\n");
      break;
      
      case 0:
	
	fils(fb_lcd, pipe_fd, &operation, semid);
    
	//printf("%d:%d \n", heure->tm_hour, heure->tm_min);
	
	exit(0);
	
      break;
      
      default :
	
    
	while (1)
	{
	    menu();
	  
	    printf ("\n");
	    printf ("       Votre choix: ");
	    fflush(stdin);
	   if((r=scanf ("%c", &choix_quit)) >= 0)
	     {
	      fflush(stdin);
	      //while (getchar() != '\n');	//vider le beffer du claver
	      printf ("\n");
    
	      if (choix_quit == 'c')		
	       {
	        covert(&result,data);
	        afiche(fb_lcd, &result, &operation, semid);
	       }
       
	      else if (choix_quit == 'q')	
	       {
	        write (pipe_fd[1], &choi_q,1);
	      
	        write (quite, "q",2);
	      
	        shmdt(save);
	        shmctl(shmid, IPC_RMID,NULL);
	        close (pipe_fd[1]);
	        close(fifo);
	        close(quite);
	        semctl(semid, 0, IPC_RMID, 0);
	      //sleep (2);
	      //write (fb_lcd,&clear,1);
	        exit(0);
	       }
	      else			printf("Valeur incoreccte\n\n");
	     }
           else 
	    {
	      
	      write (pipe_fd[1], &choi_q,1);
	      
	      write (quite, "q",2);
	    
	      shmdt(save);
	      shmctl(shmid, IPC_RMID,NULL);
	      close (pipe_fd[1]);
	      close(fifo);
	      close(quite);
	      semctl(semid, 0, IPC_RMID, 0);
	      printf("trl C\n");
	      exit(0);
	    } 
	}
    }
  }
  else printf("Vous nete pas autoriser\n");
  
  exit(0);
}