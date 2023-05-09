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

struct resultat{
  char decimal[4];
  char hexa[3];
  char bin[9];
};

int main()
{
  struct resultat result;
  int fb, bf, mk, km, i = -1, y = 0, mkquit, quite, flag = 0;
  char bef2[80], bef3[80], lcd[80], txt[80], bef4[3] = "a";
  FILE *liste;
  FILE *resulta_convertion;
  key_t key;
  int shmid;
  char *data, *save;
  
  key = ftok("lcd.c",'R');
  
  shmid = shmget(key, getpagesize(), 0644 | IPC_CREAT);
  if (shmid == -1)
  {
    perror("shmid");
    return -1;
  }
  
  save = data = shmat(shmid,(void *)0, 0);
  if (save == (void*)-1)
  {
    perror("save");
    return -1;
  }
  
  mkquit = mkfifo("quite", 0644 | O_NONBLOCK);
  if (mkquit == -1)
  {
    perror("quite");
    return -1;
  }
  
  mk = mkfifo("lcd_mkfifo", 0644);
  if (mk == -1)
  {
    perror("lcd_mkfifo");
    return -1;
  }
  
  km = mkfifo("iden_mkfifo", 0644);
    if (km == -1)
    {
      perror("iden_mkfifo");
      return -1;
    }
    
  quite = open ("quite", O_RDONLY | O_NONBLOCK);
  if (quite == -1)
  {
    perror("quite");
    return -1;
  }
  
  fb = open ("lcd_mkfifo", O_RDONLY);
  if (fb == -1)
  {
    perror("fb");
    return -1;
  }
  
  bf = open ("iden_mkfifo", O_WRONLY);
  if (bf == -1)
  {
    perror("bf");
    return -1;
  }
  
  liste = fopen ("liste.txt", "r");
  if (&liste == NULL)
  {
    perror("liste");
    return -1;
  }
  
  resulta_convertion = fopen ("convertion.txt", "a");
  if (&resulta_convertion == NULL)
  {
    perror("resulta convertion");
    return -1;
  }
    
  //while (strcmp(bef2,"quit") != 0)
  //{
  y = -1;
  do
  { 
     y++;
    read (fb, &bef2[y], 1);
  }
  while (bef2[y] != '\0');
  printf ("%s\n", bef2);
  
  y = -1;
  do
  { 
    y++;
    read (fb, &bef3[y], 1);
    
  }
  while (bef3[y] != '\0'); 
  printf ("%s\n", bef3);
  
  
  sprintf(lcd, "%s|%s",bef2 ,bef3);
  printf ("%s\n", lcd);
  
  while (feof(liste) != 1)
  {
    fscanf (liste, "%s", txt);
    printf ("%s\n", txt);
    
    i = strcmp(txt,lcd);
    printf("%d\n",i);
    
    if (i == 0)
    {
      write (bf, "oui", strlen("oui")+1);
      flag = 1;
    }
  }
      
    
  if (flag == 1)
  {
    strcpy(data,"a");
    do
    {
      //printf("%s\n",data);
      strcpy(result.decimal,data);
      strcpy(result.hexa,data+5);
      strcpy(result.bin,data+10);
      //printf("%s\n",data);
      
      while(strncmp(data, "a", 1) != 0)
      {
	printf ("Decimal:     %s\n"  , result.decimal);
	printf ("Hexadecimal: 0X%s\n", result.hexa);
	printf ("Binaire:     %s\n"  , result.bin);
	
	fprintf(resulta_convertion, "Utilisateur: %s\n	Decimal: %s\n	Hexadecimal: %s\n	Binaire: %s\n\n", bef2, result.decimal, result.hexa, result.bin);
	
	strcpy(data,"a");
      }
      //printf("%c\n",bef4);
      y = -1;
      do
      { 
	y++;
	read (quite, &bef4[y], 1);
      }
      while (bef4[y] != '\0');
      //printf ("%s\n", bef4);
      usleep(500);
    }
    while (bef4[0] != 'q');
    
    shmdt(save);
    shmctl(shmid, IPC_RMID,NULL);
  }
  else     write (bf, "non", strlen("non")+1);
  
  close(quite);
  unlink("quite");
  fclose(liste);
  close(fb);
  unlink("iden_mkfifo");  
  close(bf);
  unlink("lcd_mkfifo");
  return 0;
}