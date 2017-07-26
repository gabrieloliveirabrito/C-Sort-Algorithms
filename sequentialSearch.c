#include "sequentialSearch.h"

Chave sequentialSearch(struct sList lista, Chave chave, int *comparacoes)
{
	*comparacoes = 0;
	
	int i;
	for(i = 0; i < lista.tamanho; i++)
		if(lista.items[i].chave == chave)
			return i;
		else
			(*comparacoes)++;
	return -1;
}
