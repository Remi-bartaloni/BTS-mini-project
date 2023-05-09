#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

void man()
{
  pid-t pid;
  key_t key = 666;
  int semid, retour;
  struct sembuf operation;
  
  semid = semget(key, 1, IPC_CREAT | 0600);	//création du sémaphore
  semctl(semid, 0, SETVAL, 1);			//sémaphore 0
  operation.sem_num = 0;			//sémaphore 0
  operation.sem_flg = 0;			//On s'en occupe pas
  
  pid = fork();
  
  if(pid == 0)
  {
    operation.sem_op = -1;			//demande le sémaphore
    semop(semid, &operation, 1);		//applique le sémaphore
    .......
    .......
    operation.sem_op = 1;			//libère le sémaphore
    semop (semid, &operation, 1);		//applique le sémaphore
    exit(1);
  }
  else
  {
    operation.sem_op = -1;			//demande le sémaphore
    semop(semid, &operation, 1);		//applique le sémaphore
    .....
    .....
    operation.sem_op = 1;			//libère le sémaphore
    semop(semid, &operation, 1);		//applique le sémaphore
    wait(&retour);				//atenn la fermetur du fils
    semctl(semid, 0, IPC_RMID, 0);		//destruction du sémaphore
  }
}