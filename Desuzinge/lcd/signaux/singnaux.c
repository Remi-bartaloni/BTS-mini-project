#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

unsigned short stop = 0;


void signalhandlerc(int signal) 
{
  if (signal == SIGINT)
  {
    static unsigned short nbSignal = 0;
    nbSignal++;
    if(nbSignal == 5)	stop =1;
  }
}


int main()
{
  signal(SIGINT, signalhandlerc);
  while (!stop)
  {
    printf("Le prog travaille\n");
    sleep(1);
  }
  return 0;
}