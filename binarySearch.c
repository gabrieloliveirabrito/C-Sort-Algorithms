#include "binarySearch.h"

Chave binarySearch(struct sList lista, Chave chave, int *comparacoes)
{
	*comparacoes = 0;
	Chave direita = lista.total - 1, esquerda = 0, inicio, encontrado = 0, meio;
	
	while(esquerda <= direita && !encontrado)
	{
		meio = (esquerda + direita)	 / 2;
		
		if(lista.items[meio].chave == chave)
			encontrado = 1;
		else if(chave < lista.items[meio].chave) 
			direita = meio - 1;
		else 
			esquerda = meio + 1;
			
		if(!encontrado)
			(*comparacoes)++;
	}
	return meio;
}
