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
  int mk, fb;
  
  mk = mkfifo("myfifo", 0666);
  if (mk == -1)
  {
    perror("mkfifo");
    return -1;
  }
  
  
  fb = open ("myfifo", O_WRONLY);
  if (fb == -1)
  {
    perror("fb");
    return -1;
  }
  

    write (fb, "teste", strlen("teste"));

  
  close(fb);
  unlink("myfifo");
  return 0;
}