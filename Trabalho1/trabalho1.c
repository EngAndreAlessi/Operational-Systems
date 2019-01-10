#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(void)
{
	pid_t PID_A, PID_B, PID_C, PID_D, PID_E, PID_F, PID_G, PID_H, PID_I;
	PID_A = getpid();
	printf("\nCriado proc-a: PID = %ld PPID = %ld\n",(long int)PID_A,(long int)getppid());
	if(fork()>0) //Pai: processo A
	{
		wait(NULL);
	}
	else //Filho: processo B 
	{
		PID_B = getpid();
		printf("\nCriado proc-b: PID = %ld PPID = %ld\n",(long int)PID_B,(long int)getppid());
		if(fork()>0) //Pai: processo B
		{
			wait(NULL);
		}
		else //Filho: processo C
		{
			PID_C = getpid();
			printf("\nCriado proc-c: PID = %ld PPID = %ld\n",(long int)PID_C,(long int)getppid());
		}
	}
	if(getpid()==PID_A)
	{
		if(fork()>0) //Pai: processo A
		{
			wait(NULL);
		}
		else //Filho: processo D
		{
			PID_D = getpid();
			printf("\nCriado proc-d: PID = %ld PPID = %ld\n",(long int)PID_D,(long int)getppid());
		}
	}
	if(getpid()==PID_A)
	{
		if(fork()>0) //Pai: processo A
		{
			wait(NULL);
		}
		else //Filho: processo E
		{
			PID_E = getpid();
			printf("\nCriado proc-e: PID = %ld PPID = %ld\n",(long int)PID_E,(long int)getppid());
			if(fork()>0) //Pai: processo E
			{
				wait(NULL);
			}
			else //Filho: processo F
			{
				PID_F = getpid();
				printf("\nCriado proc-f: PID = %ld PPID = %ld\n",(long int)PID_F,(long int)getppid());
			}
			if(getpid()==PID_F)
			{
				if(fork()>0) //Pai: processo F
				{
					wait(NULL);
				}
				else //Filho: processo G
				{
					PID_G = getpid();
					printf("\nCriado proc-g: PID = %ld PPID = %ld\n",(long int)PID_G,(long int)getppid());
				}
			}
			if(getpid()==PID_F)
			{
				if(fork()>0) //Pai: processo F
				{
					wait(NULL);
				}
				else //Filho: processo H
				{
					PID_H = getpid();
					printf("\nCriado proc-h: PID = %ld PPID = %ld\n",(long int)PID_H,(long int)getppid());
				}
			}
			if(getpid()==PID_F)
			{
				if(fork()>0) //Pai: processo F
				{
					wait(NULL);
				}
				else //Filho: processo I
				{
					PID_I = getpid();
					printf("\nCriado proc-i: PID = %ld PPID = %ld\n",(long int)PID_I,(long int)getppid());
				}
			}
		}		
	}
	if(PID_G==getpid())
	{
		printf("\nMatando o proc-g ( ͡° ͜ʖ ͡°)\n");
		exit(7);
	}
	if(PID_H==getpid())
	{
		printf("\nMatando o proc-h ( ͡° ͜ʖ ͡°)\n");
		exit(7);
	}
	if(PID_I==getpid())
	{
		printf("\nMatando o proc-i ( ͡° ͜ʖ ͡°)\n");
		exit(7);
	}
	if(PID_F==getpid())
	{
		printf("\nMatando o proc-f ( ͡° ͜ʖ ͡°)\n");
		exit(7);
	}
	if(PID_E==getpid())
	{
		printf("\nMatando o proc-e ( ͡° ͜ʖ ͡°)\n");
		exit(7);
	}
	if(PID_D==getpid())
	{
		printf("\nMatando o proc-d ( ͡° ͜ʖ ͡°)\n");
		exit(7);
	}
	if(PID_C==getpid())
	{
		printf("\nMatando o proc-c ( ͡° ͜ʖ ͡°)\n");
		exit(7);
	}
	if(PID_B==getpid())
	{
		printf("\nMatando o proc-b ( ͡° ͜ʖ ͡°)\n");
		exit(7);
	}
	if(PID_A==getpid())
	{
		printf("\nMatando o proc-a ( ͡° ͜ʖ ͡°)\n");
		exit(7);
	}
	
	return 0;
}
