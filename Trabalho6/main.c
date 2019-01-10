#include "headers.h"

jantar *j;

void inicializa(jantar *j)
{
	j->count=M;
	sem_init(&(j->cozinha),1,0);
	sem_init(&(j->comida),1,M+1);
	sem_init(&(j->mutex),1,1);
	sem_init(&(j->enchendo),1,0);
	printf("Inicializado\n");
}

int main(void)
{
	int shmid;
	shmid = shmget(KEY,sizeof(jantar),IPC_CREAT|SHM_R|SHM_W);

	if(shmid==-1)
	{
		perror("Erro no shmget\n");
		exit(1);
	}
	printf("shmid: %d\n",shmid);

	j = (jantar *)shmat(shmid,NULL,0);
	inicializa(j);

	pid_t pid;
	pid = fork();
	if(pid>0)
	{
		execl("./gaules","gaules",NULL);
	}
	else if(pid==0)
	{
		execl("./cozinheiro","cozinheiro",(char *)NULL);
	}
	sleep(50);
	return 0;
}