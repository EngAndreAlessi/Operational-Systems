#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <time.h>

#define M 17
#define NGauleses 5
#define TRUE 1

sem_t cozinha, comida, enchendo;

void inicializa()
{
	sem_init(&cozinha,0,0);
	sem_init(&comida,0,M+1);
	sem_init(&enchendo,0,0);
}

int main(void)
{
	int count = 0;
	inicializa();
	#pragma omp parallel num_threads(NGauleses + 1)
	{
		int id = omp_get_thread_num();

		if(id < NGauleses)
		{
			while(TRUE)
			{
				sleep(1);
				sem_wait(&comida);
				#pragma omp critical
				{
					count++;
					if(count>M)
					{
						if(id==0)
						{
							printf("Gaules a(0) acordou o cozinheiro\n");
						}
						else if(id==1)
						{
							printf("Gaules n(1) acordou o cozinheiro\n");
						}
						else if(id==2)
						{
							printf("Gaules d(2) acordou o cozinheiro\n");
						}
						else if(id==3)
						{
							printf("Gaules r(3) acordou o cozinheiro\n");
						}
						else if(id==4)
						{
							printf("Gaules e(4) acordou o cozinheiro\n");
						}
						sem_post(&cozinha);
						sem_wait(&enchendo);
						count=1;
					}					
				}
				if(id==0)
					{
						printf("Gaules a(%d) consumiu o javali %d\n",id,count);
					}
					else if(id==1)
					{
						printf("Gaules n(%d) consumiu o javali %d\n",id,count);
					}
					else if(id==2)
					{
						printf("Gaules d(%d) consumiu o javali %d\n",id,count);
					}
					else if(id==3)
					{
						printf("Gaules r(%d) consumiu o javali %d\n",id,count);
					}
					else if(id==4)
					{
						printf("Gaules e(%d) consumiu o javali %d\n",id,count);
					}
			}
		}
		else
		{
			while(TRUE)
			{
				sleep(3);
				int i;
				sem_wait(&cozinha);
				for(i=1;i<=M;i++)
				{
					printf("O cozinheiro produziu o javali %d\n",i);
					sem_post(&comida);
				}
				sem_post(&enchendo);
			}
		}
	}
	return 0;
}
