#include <stdio.h>
#include <stdlib.h>


int main()
{
  int pid, count = 0, stuff = 0;
  char bef[80];
  
  
  
  FILE *f; 
  
  f = fopen ("Fork.txt", "w+");
  
  if (f == 0)
  {
   printf("ERREUR\n");
   exit (0);
  }
      
  
  pid = fork();
  
  switch (pid)
  {
    case -1: printf ("erreur\n");
    break;
    
    case 0:
      sleep(2);
      
	fprintf(f, "%s", " et moi le fils !\n");	
	
	fseek (f, 0, SEEK_SET);
      
   fread(bef, 80, 1, f);
      
   printf ("%s\n", bef);
      
      exit(0);
    break;
    
    default :
      
      fprintf(f, "%s", "je suis le père");
      
      
  }
  
  fclose(f);
  
  exit (0);
}