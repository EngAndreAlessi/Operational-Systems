#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>
#define M 17
#define NGauleses 5
int count;
sem_t cozinha, comida, enchendo;
pthread_mutex_t mutex;
pthread_t gauleses[NGauleses];
pthread_t cozinheiro_t;

void inicializa()
{
	count = 0;
	sem_init(&cozinha,0,0);
	sem_init(&comida,0,M+1);
	sem_init(&enchendo,0,0);
	pthread_mutex_init(&mutex,NULL);
}

void *gaules(void *arg)
{
	long i = (long)arg;
	while(true)
	{
		sleep(5);
		sem_wait(&comida);
		pthread_mutex_lock(&mutex);
		count++;
		printf("Count: %d\n",count);
		if(count>M)
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
			sem_post(&cozinha);
			sem_wait(&enchendo);
			count=1;
		}
		pthread_mutex_unlock(&mutex);
		if(i==0)
		{
			printf("Gaules a(0) comendo\n");
		}
		else if(i==1)
		{
			printf("Gaules n(1) comendo\n");
		}
		else if(i==2)
		{
			printf("Gaules d(2) comendo\n");
		}
		else if(i==3)
		{
			printf("Gaules r(3) comendo\n");
		}
		else if(i==4)
		{
			printf("Gaules e(4) comendo\n");
		}
	}
}

void *cozinheiro(void *arg)
{
	int i;
	while(true)
	{
		sleep(5);
		sem_wait(&cozinha);
		for(i=1;i<=M;i++)
		{
			printf("Cozinheiro cozinhou javali %i\n",i);
			sem_post(&comida);
		}
		sem_post(&enchendo);
	}
}

int main(void)
{
	long i;
	inicializa();
	pthread_create(&cozinheiro_t,NULL,cozinheiro,NULL);
	for(i=0;i<NGauleses;i++)
	{
		pthread_create(&gauleses[i],NULL,gaules,(void *)i);
	}
	pthread_join(cozinheiro_t,NULL);
	for(i=0;i<NGauleses;i++)
	{
		pthread_join(gauleses[i],NULL);
	}

	sem_close(&cozinha);
	sem_close(&comida);
	sem_close(&enchendo);
	pthread_mutex_destroy(&mutex);

	return 0;
}