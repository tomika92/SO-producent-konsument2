#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int c, char* vect[])
{
	system("clear");

	FILE *f;
	int pipe;
	char sciezka[20] = "./kons/wy_";
	char pid[10];
	sprintf(pid,"%d",getpid());
	strcat(sciezka,pid);
	f=fopen(sciezka,"w");
	if(f==NULL)
	{
		printf("Blad otwieraniu pliku\n");
		exit(1);	
	}
	char bufor='a';

	pipe=open("/tmp/fifo",O_RDONLY|O_NONBLOCK);//uzyskiwanie dostepu do kolejki
	if(pipe==-1)
	{
		printf("Nie uzyskano dostepu do kolejki\n");
		exit(1);
	}

	while(bufor!=EOF)
	{
		sleep(1);
		
		int readstatus=read(pipe,(void*)&bufor,1);//pobieranie produktu
		if(readstatus==0)
		{
			printf("Wszystkie znaki zostaly pobrane\n");
			break;
		}
		if(readstatus==-1)
		{
			printf("Blad funkcji read\n");
			exit(1);
		}
		
		printf("%c\n",bufor);
		fprintf(f,"%c",bufor);
		
	}
		
	close(pipe);
	fclose(f);
	unlink("/tmp/fifo");	
}