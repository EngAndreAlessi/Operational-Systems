#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>

void quicksort(int *valor, int esquerda, int direita)
{
	int i,j,x,y;
	i = esquerda;
	j = direita;
	x = valor[(esquerda+direita)/2];
	while(i <= j)
	{
		while(valor[i] < x && i < direita)
		{
			i++;
		}
		while(valor[j] > x && j > esquerda)
		{
			j--;
		}
		if(i <= j)
		{
			y = valor[i];
			valor[i] = valor[j];
			valor[j] = y;
			i++;
			j--;
		}
	}
	if(j > esquerda)
	{
		quicksort(valor,esquerda,j);
	}
	if(i < direita)
	{
		quicksort(valor,i,direita);
	}
}

void bolha(int *vet, int tamanho)
{
	int i,j,temp;
	for(i=0;i<tamanho;i++)
	{
		for(j=(i+1);j<tamanho;j++)
		{
			if(vet[j]<vet[i])
			{
				temp = vet[i];
				vet[i] = vet[j];
				vet[j] = temp;
			}
		}
	}
}

void printa_vet(int *v, int tam)
{
	int i;
	for(i=0;i<tam;i++)
	{
		printf("%d ",v[i]);
	}
	printf("\n");
}

int main(int argc, char *argv[])
{
	int tam = argc-1;
	int v[tam];
	int i;
	//printf("argc = %d\n",argc);
	for(i=1;i<argc;i++)
	{
		v[i-1] = atoi(argv[i]);
	}
	//printa_vet(v,tam);
	pid_t pid,pid_pai;
	pid_pai = getpid();
	pid = fork();
	if(pid > 0)
	{
		bolha(v,tam);
		kill(pid,SIGKILL);
		printf("Sou o pai, matei meu filho!\n");
		printf("Vetor ordenado pelo pai:\n");
		printa_vet(v,tam);
	}
	else
	{
		quicksort(v,0,tam);
		kill(pid_pai,SIGKILL);
		printf("Sou o filho, matei meu pai!\n");
		printf("Vetor ordenado pelo filho:\n");
		printa_vet(v,tam);
	}
}