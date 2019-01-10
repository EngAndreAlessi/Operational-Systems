#include <stdio.h> 
#include <unistd.h>
#include <pthread.h>
#include <math.h>
#include <time.h>
#define NUM_THREAD 4
#define CONT 1000000000

double resultado_parcial[NUM_THREAD];

void* body_thread(void *arg)
{
	long n;
	long j = 0;
	long i = (long)arg;
	for(n=i*CONT/NUM_THREAD;n<(i+1)*CONT/NUM_THREAD;n++)
	{
		resultado_parcial[i] += pow(-1.0,n)/(2.0*n+1.0);
	}
	return NULL;
}

double soma_vet(double *v)
{
	double ret=0;
	long i;
	for(i=0;i<NUM_THREAD;i++)
	{
		ret+=v[i];
	}
	return ret;
}

int main(void)
{
	clock_t start_t, end_t;
	pthread_t thread[NUM_THREAD];
	pthread_attr_t attr;  
	pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	long result_long;
	long i;
	start_t = clock();
	//printf("Start: %lf\n",(double)start_t);
	for(i=0;i<NUM_THREAD;i++)
	{
		pthread_create(&thread[i],&attr,body_thread,(void *)i);
	}
	for(i=0;i<NUM_THREAD;i++)
	{
		pthread_join(thread[i],NULL);
	}
	double pi = 4*soma_vet(resultado_parcial);
	end_t = clock();
	//printf("End: %lf\n",(double)end_t);
	printf("Numero de threads: %d\npi: %.12lf\nTime: %lf s\n",NUM_THREAD,pi,(double)(end_t - start_t) / CLOCKS_PER_SEC);
	pthread_attr_destroy(&attr);
	return 0;
}