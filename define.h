#pragma once

//Caso o compilador n�o haja uma constante para definir um ponteiro, inst�ncia nula, defina
#ifndef NULL
	#define NULL (void*)\0
#endif

//#define DEBUG
//#define DOUBLE_CHECK
#define SORT_INCREMENT		100				//Constante para incrementar o n�mero de chaves para o teste
#define MAX_RANDC_TOSEED	RAND_MAX - 1 	//Constante para gera��o de uma nova seed
#define Chave unsigned long 				//Defini��o de tipo de chave global
