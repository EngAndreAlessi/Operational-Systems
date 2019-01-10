#include "headers.h"
jantar *j;
pthread_t cozinheiro_t;

void *cozinheiro(void *arg)
{
	int i;
	while(TRUE)
	{
		sleep(2);
		sem_wait(&(j->cozinha));
		for(i=1;i<=M;i++)
		{
			printf("Cozinheiro cozinhou o javali %d\n",i);
			sem_post(&(j->comida));
		}
		sem_post(&(j->enchendo));
	}
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

	printf("shmid do cozinheiro: %d\n",shmid);

	j = (jantar *)shmat(shmid,NULL,0);

	pthread_create(&cozinheiro_t,NULL,cozinheiro,NULL);

	sleep(50);
}