#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int c, char* vect[])
{
	if(c!=2)
	{
		printf("Niepoprawna liczba argmuentow.\n");
		exit(1);	
	}
	int liczba_prod=atoi(vect[1]);
	if(liczba_prod==INT_MAX||liczba_prod==INT_MIN)
	{
		printf("Blad funkcji atoi\n");
		exit(1);	
	}
	system("clear");
	
	FILE *f;
	char sciezka[20] = "./prod/we_";
	char pid[10];
	sprintf(pid,"%d",getpid());
	strcat(sciezka,pid);
	
	srand(getpid());
	
	int pipe;
	char znak;
	int i,j;
	
	if(access("/tmp/fifo",F_OK)==-1)//uzyskiwanie dostepu do kolejki
	{
		if(mkfifo("/tmp/fifo",0666))
		{
			printf("Blad towrzenia kolejki\n");
			exit(1)	;
		}

		system("rm ./prod/we_*");
		system("rm ./kons/wy_*");
		system("clear");	
	}
	
	pipe=open("/tmp/fifo",O_WRONLY);

	if(pipe==-1)
	{
		printf("Blad otwarcia kolejki\n");
		exit(1);
	}
		
	f=fopen(sciezka,"w");
	
	if(f==NULL)
	{
		printf("Blad otwarcia pliku\n");
		exit(1);	
	}
	
	for(j=0;j<liczba_prod;j++)
	{
		printf("Przetwarzanie produktu %d\n", j);		
			
		for(i=0;i<1;i++)
		{
			znak=(char)(rand()%25+65);
			if(write(pipe,(void*)&znak,1)==EOF)//zapisywanie znakow
			{
				printf("Blad funkcji write\n");
				exit(1);	
			}
			fprintf(f,"%c\n",znak);		
		}
	}	
	fclose(f);	
}