#include "headers.h"
int pfd[2];

int main()
{
	pipe(pfd);
	pid_t pid;
	int i;

	for(i=0;i<NGauleses;i++)
	{
		if( (pid=fork()) == 0 )
		{
			close(pfd[READ]);
			char canal[8],id[8];
			sprintf(id,"%d",i+1);
			sprintf(canal,"%d",pfd[WRITE]);
			execl("./gaules","gaules",canal,id,NULL);
		}
	}

	if( (pid=fork()) == 0 )
	{
		close(pfd[WRITE]);
		char canal[8];
		sprintf(canal,"%d",pfd[READ]);
		execl("./cozinheiro","cozinheiro",canal,NULL);
	}

	sleep(50);
}