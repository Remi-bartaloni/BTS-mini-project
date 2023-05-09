#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

unsigned short stop = 0;


void handler(int signal) 
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
  struct sigaction new_action, old_action;
  //sigset_t ens1;
  
  new_action.sa_handler = handler;
  //sigemptyset(&ens1);
  //sigaddset(&ens1,SIGUSR1);
  //sigprocmask(SIG_SETMASK, &ens1, NULL);
  sigemptyset(&new_action.sa_mask);
  new_action.sa_flags = 0;
  sigaction(SIGINT,&new_action,& old_action);
  
  while (!stop)
  {
    printf("Le prog travaille\n");
    sleep(1);
  }
  return 0;
}