#pragma once

//Caso o compilador não haja uma constante para definir um ponteiro, instância nula, defina
#ifndef NULL
	#define NULL (void*)\0
#endif

//#define DEBUG
//#define DOUBLE_CHECK
#define SORT_INCREMENT		100				//Constante para incrementar o número de chaves para o teste
#define MAX_RANDC_TOSEED	RAND_MAX - 1 	//Constante para geração de uma nova seed
#define Chave unsigned long 				//Definição de tipo de chave global
