#include <stdio.h>
#include <mpi.h>
#include <unistd.h>
#include <omp.h>

#define M 17
#define TRUE 1
#define NGauleses 5

char nome[NGauleses+1] = "andre\0";
int count=0;

int main(void)
{
	MPI_Init(NULL,NULL);
	MPI_Status status;
	int tag,rank,i;
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	char msg[100];
	if(rank==0)
	{
		while(TRUE)
		{
			sleep(1);
			for(i=1;i<=M;i++)
			{
				printf("Cozinheiro cozinhou o javali %d\n",i);
				MPI_Send(msg,sizeof(msg),MPI_CHAR,1,tag,MPI_COMM_WORLD);
			}
			MPI_Recv(msg,sizeof(msg),MPI_CHAR,1,tag,MPI_COMM_WORLD,&status);			
		}
	}
	else
	{
		#pragma omp parallel num_threads(NGauleses)
		{
			int id = omp_get_thread_num();
			while(TRUE)
			{
				MPI_Recv(msg,sizeof(msg),MPI_CHAR,0,tag,MPI_COMM_WORLD,&status);
				sleep(1);
				printf("Gaules %c(%d) comendo javali\n",nome[id],id);
				count++;
				#pragma omp critical
				{
					if(count==17)
					{
						printf("Gaules %c(%d) acordou o cozinheiro\n",nome[id],id);
						MPI_Send(msg,sizeof(msg),MPI_CHAR,0,tag,MPI_COMM_WORLD);
						count=1;
					}
				}
			}
		}
	}
}