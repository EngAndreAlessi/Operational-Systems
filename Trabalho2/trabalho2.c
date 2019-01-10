#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
int cont=0;
void trata_SIGINT(int sig)
{
	cont++;
}
void trata_SIGTSTP(int sig)
{
	printf("\nFoi recebido %d sinais SIGINT!\n",cont);
}
int main(void)
{

	while(cont<10)
	{
		signal(SIGINT,trata_SIGINT);
		signal(SIGTSTP,trata_SIGTSTP);
		if(cont==10)
		{
			char resposta;
			printf("\nReally exit? (Y/n) ");
			alarm(5);
			scanf(" %c",&resposta);
			if(resposta=='n'||resposta=='N')
			{
				cont=0;
				alarm(0);
			}
			else if(resposta=='Y'||resposta=='y')
			{
				raise(SIGKILL);
			}
		}
	}
	return 0;
}
