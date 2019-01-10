#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <errno.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#define M 17
#define NGauleses 5
#define TRUE 1

#define KEY 666

typedef struct jantar
{
	sem_t cozinha, comida, mutex, enchendo;
	int count;
}jantar;