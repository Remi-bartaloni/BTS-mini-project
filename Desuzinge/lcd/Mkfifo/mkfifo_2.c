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
  int fb;
  char bef[50];
  
  fb = open ("myfifo", O_RDONLY);
  if (fb == -1)
  {
    perror("fb");
    return -1;
  }
  
    read (fb, bef, 6);
    printf ("%s", bef);
  
  close(fb);
  return 0;
}