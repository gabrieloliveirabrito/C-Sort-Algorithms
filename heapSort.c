#include "heapSort.h"

unsigned int heapSort(struct sList *lista)
{
	int i;
	unsigned int trocas = 0;
	for(i = (lista->tamanho - 1) / 2; i >= 0; i--)
		criaHeap(lista, i, lista->total - 1);
		
	for(i = lista->total - 1; i >= 1; i--)
	{
		struct sItem aux = copiaItem(lista->items[0]);
		lista->items[0] = copiaItem(lista->items[i]);
		lista->items[i] = aux;
		trocas++;
		criaHeap(lista, 0, i - 1);
	}
	return trocas;
}

void criaHeap(struct sList *lista, int i, int f)
{
	struct sItem aux = copiaItem(lista->items[i]);
	int j = 2 * i + 1;
	
	while(j <= f)
	{
		if(j < f)
			if(lista->items[j].chave < lista->items[j+1].chave) 
				j++;
			
		if(aux.chave < lista->items[j].chave)
		{
			lista->items[i] = copiaItem(lista->items[j]);
			i = j;
			j = 2 * i + 1;
		}
		else
			j = f + 1;
	}
	lista->items[i] = aux;
}
