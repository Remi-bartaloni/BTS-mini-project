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

void client(char ip[])
{   
	char bef[1023];
    int servSocket;
    struct sockaddr_in serverAddr, clientAddr;
    struct timeval ti;
    int n, taille;
    fd_set fd;
	char buffer[255];

	FD_ZERO(&fd);
	bzero(&serverAddr, sizeof(struct sockaddr_in));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(14);
	serverAddr.sin_addr.s_addr = inet_addr(ip);
		
    if((servSocket = socket(AF_INET, SOCK_DGRAM, 0)) != -1)
    {
		if((bind(servSocket, (struct sockaddr*)&serverAddr, sizeof(struct sockaddr_in))) >= 0)
		{
			printf("serveur UDP %s:%d\n", inet_ntoa(serverAddr.sin_addr), ntohs(serverAddr.sin_port));
			while(1)
			{
				ti.tv_sec=2;
				ti.tv_usec=0;
				FD_SET(servSocket, &fd);
				
				if(select(servSocket+1, &fd, NULL, NULL, &ti) == 1)
				{
					taille = sizeof(struct sockaddr_in);
					printf("trame de demande recue\n");
					if(recvfrom(servSocket, bef, 255, 0, (struct sockaddr*)&clientAddr, &taille) >= 0)
					{
						heur(buffer);
						printf("demande de %s:%d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
						printf("==>%s\n",buffer);
						sendto(servSocket, buffer, strlen(buffer), 0, (struct sockaddr*)&clientAddr, sizeof(struct sockaddr_in));
					}
					else    printf("recvfrom: \n");
				}
				else    printf("Timeout atteint\n");
			}
			close(servSocket);
		}
		else    perror("bind:");
    }
    else    perror("socket:");
}



int main (int argc, char **argv)
{
   
    if(argc != 2)
    {
        printf("Il faux maitre l'IP en argument\n");
        exit (0);
    }
	printf("serveur nist udp v 1.0\n");
    client(argv[1]);    
    exit (0);
}