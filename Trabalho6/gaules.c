#include "headers.h"
jantar *j;
pthread_t gauleses[NGauleses];

void *gaules(void *arg)
{
	long i = (long)arg;
	while(TRUE)
	{
		sleep(2);
		sem_wait(&(j->comida));
		sem_wait(&(j->mutex));
		if(i==0)
		{
			printf("Gaules a(0) comendo o javali %d\n",j->count);
		}
		else if(i==1)
		{
			printf("Gaules n(1) comendo o javali %d\n",j->count);
		}
		else if(i==2)
		{
			printf("Gaules d(2) comendo o javali %d\n",j->count);
		}
		else if(i==3)
		{
			printf("Gaules r(3) comendo o javali %d\n",j->count);
		}
		else if(i==4)
		{
			printf("Gaules e(4) comendo o javali %d\n",j->count);
		}
		j->count--;
		if(j->count==0)
		{
			if(i==0)
			{
				printf("Gaules a(0) acordou cozinheiro\n");
			}
			else if(i==1)
			{
				printf("Gaules n(1) acordou cozinheiro\n");
			}
			else if(i==2)
			{
				printf("Gaules d(2) acordou cozinheiro\n");
			}
			else if(i==3)
			{
				printf("Gaules r(3) acordou cozinheiro\n");
			}
			else if(i==4)
			{
				printf("Gaules e(4) acordou cozinheiro\n");
			}
			sem_post(&(j->cozinha));
			sem_wait(&(j->enchendo));
			j->count=M;
		}
		sem_post(&(j->mutex));
	}
}

int main(void)
{
	int shmid;
	shmid = shmget(KEY,sizeof(jantar),IPC_CREAT|SHM_R|SHM_W);
	if(shmid==-1)
	{
		perror("Erro no shmget\n");
		exit(1);printf("shmid: %d\n",shmid);
	}

	printf("shmid dos gauleses: %d\n",shmid);

	j = (jantar *)shmat(shmid,NULL,0);

	long i;
	for(i=0;i< NGauleses;i++)
	{
		pthread_create(&gauleses[i],NULL,gaules,(void *)i);
	}
	sleep(50);
}