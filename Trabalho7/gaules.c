#include "headers.h"

#define MAX 8

int canal;
int id;

int main(int argc,char *args[])
{
	id = atoi(args[2]);
	canal = atoi(args[1]);
	char gaules[MAX];

	while(TRUE)
	{
		read(canal,gaules,MAX);
		if(id==0)
		{
			printf("Gaules a(0) comendo\n");
		}
		else if(id==1)
		{
			printf("Gaules n(1) comendo\n");
		}
		else if(id==2)
		{
			printf("Gaules d(2) comendo\n");
		}
		else if(id==3)
		{
			printf("Gaules r(3) comendo\n");
		}
		else if(id==4)
		{
			printf("Gaules e(4) comendo\n");
		}
		sleep(1);
	}
	return 0;
}