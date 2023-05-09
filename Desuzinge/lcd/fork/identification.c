#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <time.h>


int main()
{
  int fb, mk, i = -1, o = -1;
  char bef2[6] = "no", bef3[3] = "no";
  
  
  mk = mkfifo("lcd_mkfifo", 0666);
  if (mk == -1)
  {
    perror("lcd_mkfifo");
    return -1;
  }
  
  fb = open ("lcd_mkfifo", O_RDONLY);
  if (fb == -1)
  {
    perror("fb");
    return -1;
  }
    
    read (fb, bef2, 4);
    bef2[4] = '\0';
    printf ("%s ", bef2);
    
    read (fb, bef3, 2);
    bef3[2] = '\0';
    printf ("%s\n", bef3);
  
  close(fb);
  unlink("iden_mkfifo");
  
  
   mk = mkfifo("iden_mkfifo", 0666);
    if (mk == -1)
    {
      perror("iden_mkfifo");
      return -1;
    }
    
    
    fb = open ("iden_mkfifo", O_WRONLY);
    if (fb == -1)
    {
      perror("fb");
      return -1;
    }
  
  
  i = strcmp(bef2,"test");
  o = strcmp(bef3,"15");
  
  if (i == 0 && o == 0)    	write (fb, "oui", strlen("oui"));
  else 				write (fb, "non", strlen("non"));
    
    
    
  close(fb);
  unlink("iden_mkfifo");
  return 0;
}