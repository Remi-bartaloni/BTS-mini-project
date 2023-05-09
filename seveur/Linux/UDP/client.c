#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define JJJJJ_01_01_2006 53735
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>    
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

static int jour_mois [2] [13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};


int bissextile (int annee)
{
    return((((annee % 4) == 0) &&((annee % 100) != 0)) || ((annee %400) == 0));
}

int numero_jour (int annee, int mois, int jour)
{
    int i, bis;
    
    for(bis = bissextile(annee), i = 1; i < mois; i++) jour += jour_mois [bis] [i];
    return(jour);
}

int calcul_JJJJJ(int annee, int mois, int jour)
{
    int r = -1, i;
    if((annee >= 2006) && (mois >= 1) && (mois <= 12) && (jour >= 1) && (jour <= jour_mois[bissextile (annee)][mois]))
        for(i = 2006, r = JJJJJ_01_01_2006 + numero_jour(annee,mois,jour); i < annee; i++, r += bissextile(i) ? 366:365);
    return(r);
}

void heur(char gmt[])
{
    time_t t;
    char bef[20], bef2[20], bef3[20];
    struct tm heure;
    
    t = time(NULL);
    gmtime_r(&t,&heure);
    
    if(heure.tm_year < 2000) heure.tm_year = 2000 + heure.tm_year %100;
    
    sprintf (bef ,"%5d", calcul_JJJJJ(heure.tm_year, heure.tm_mon + 1, heure.tm_mday));
    //printf ("nobre de jour ecouler : %s\n", bef);
    
    sprintf (bef2   ,"%.2d-%.2d-%.2d", heure.tm_year%100, heure.tm_mon + 1, heure.tm_mday);
    //printf("date : %s\n", bef2);
    
    sprintf (bef3   ,"%.2d:%.2d:%.2d", heure.tm_hour, heure.tm_min, heure.tm_sec);
    //printf("heur : %s\n\n", bef3);
    
    sprintf (gmt, "%s %s %s 00 0 0 000.0 LOC(NIST) *", bef, bef2, bef3);
    //printf("%s\n",gmt);   
}

time_t decode_nist(char *s)
{
 time_t r=0;
 struct tm d;
 char c, nist[30];
 int bidj, bid1, bid2, bid3, bid4, bid5;
 
 if(s)
   {
    while((*s == '\n') || (*s == ' ') || (*s == '\t')) s++;
    if(*s)
      {
       bzero(&d,sizeof(d));
       sscanf(s,"%05d %02d-%02d-%02d %02d:%02d:%02d %02d %d %d %03d.%d %s %c",&bidj,&d.tm_year,&d.tm_mon,
              &d.tm_mday,&d.tm_hour,&d.tm_min,&d.tm_sec,&bid1,&bid2,&bid3,&bid4,&bid5,nist,&c);
       if((d.tm_year >= 0) && (d.tm_year <= 99) &&
          (d.tm_mon  >= 1) && (d.tm_mon  <= 12) &&
          (d.tm_mday >= 1) && (d.tm_mday <= 31) && // test incomplet
          (d.tm_hour >= 0) && (d.tm_hour <  24) &&
          (d.tm_min  >= 0) && (d.tm_year <  60) &&
          (d.tm_sec  >= 0) && (d.tm_sec  <  60) && (c == '*'))
          { 
           d.tm_year +=100;
           d.tm_mon--;
           r = mktime(&d);
          }
      }
   }
 return(r);
}

time_t client(char ip[], char buffer[])
{   
    int clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    struct timeval ti;
    int n;
    time_t r=0;
    fd_set fd;

	FD_ZERO(&fd);
	bzero(&serverAddr, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(14);
	serverAddr.sin_addr.s_addr = inet_addr(ip);

	bzero(&clientAddr, sizeof(clientAddr));
	clientAddr.sin_family = AF_INET;
	clientAddr.sin_port = htons(5000);
	clientAddr.sin_addr.s_addr = 0; ///inet_addr(ip);
		
	printf("tserveur: %s:%d", inet_ntoa(serverAddr.sin_addr), ntohs(serverAddr.sin_port));	
    if((clientSocket = socket(AF_INET, SOCK_DGRAM, 0)) != -1)
    {
		
		if((bind(clientSocket, (struct sockaddr*)&clientAddr, sizeof(struct sockaddr_in))) >= 0)
		{
			 printf("bind fait\n");
			if(sendto(clientSocket,"", 0, 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) >= 0) 
			{
				printf("trame nist demandee à: %s:%d\n", inet_ntoa(serverAddr.sin_addr), ntohs(serverAddr.sin_port));
				ti.tv_sec=2;
				ti.tv_usec=0;
				FD_SET(clientSocket, &fd);
				if(select(clientSocket+1, &fd, NULL, NULL, &ti) == 1)
				{
					printf("trame en attente\n");
					n=recvfrom(clientSocket, buffer, 255, 0, NULL, NULL);
					if(n>0)
					{
						
						buffer[n]=0;
						printf("%d:==> %s\n",n,buffer);
						r = decode_nist(buffer);
					}
				}
				else    printf("Timeout atteint\n");
			}
        else    perror("sendto:");    
        close(clientSocket);
		}
		else    perror("bind:");
    }
    else    perror("socket:");
    return(r);
}





int main (int argc, char **argv)
{
    time_t serv, loc;
    char gmt[255];
    char buffer[255];
    
    if(argc != 2)
    {
        printf("Il faux mettre l'IP en argument\n");
        exit (0);
    }
    
	printf("client v1.4\n");
    serv = client(argv[1], buffer);
    heur(gmt);
    
    printf("heur du serveur:%s\n", buffer);
    printf("heur locale:\n%s\n",gmt);
    
    loc = decode_nist(buffer);
    
    printf("\nEcart: %ds\n",serv-loc);
    
    exit (0);
}