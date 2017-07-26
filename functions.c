#include "includes.h"

//Função random para números aleatórios limitados.
//O algorítmo gera uma nova seed caso seu registro alcance o máximo de chamadas, ou seu valor seja igual a -1
int random(int min, int max)
{
	if(randReg.n == -1 || ++randReg.n > MAX_RANDC_TOSEED)
	{
		randReg.n = 0;
		srand(time(NULL));
	}
	return min + rand() % (max - min);
}

//Retorna a porcentagem entre um valor e seu máximo
int percentage(int current, int total)
{
	return (current * 100) / total;
}


void iniciaTimer()
{
	clock_gettime(CLOCK_MONOTONIC, &timer.start);
}

double paraTimer()
{
	clock_gettime(CLOCK_MONOTONIC, &timer.end);
	
	return ((timer.end.tv_sec - timer.start.tv_sec) * 1.0e3) + ((timer.end.tv_nsec - timer.start.tv_nsec) / 1.0e6);
}
