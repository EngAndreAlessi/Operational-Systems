#include "headers.h"

#define MAX 8

int canal;

int main(int argc,char *args[])
{
	canal = atoi(args[1]);
	char cozinheiro[MAX];

	while(TRUE)
	{
		write(canal,cozinheiro,MAX);
		printf("Cozinheiro cozinhou\n");
	}
}