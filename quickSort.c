#include "quickSort.h"

//Método utilizado para o delegate padronizado
unsigned int quickSort(struct sList* lista)
{
	return QuickSort(lista, 0, lista->total - 1);
}


//Algorítimo QuickSort - seu retorno é o número de trocas realizadas
unsigned int QuickSort(struct sList* lista, int inicio, int fim)
{
	int pivo = 0;
	unsigned int trocas = 0;
	if(fim > inicio)
	{
		pivo = particiona(lista, inicio, fim, &trocas);
		trocas += QuickSort(lista, inicio, pivo - 1);
		trocas += QuickSort(lista, pivo + 1, fim);
	}
	return trocas;
}

//Algorítmo Particiona, parte do quicksort
//Incrementa o valor do ponteiro trocas em cada ação
int particiona(struct sList *lista, int inicio, int fim, unsigned int *trocas)
{
	int esq = inicio;
	int dir = fim;
	struct sItem pivo = copiaItem(lista->items[inicio]);
	
	while(esq < dir)
	{
		while(lista->items[esq].chave <= pivo.chave) esq++;
		while(lista->items[dir].chave > pivo.chave) dir--;
		
		if(esq < dir)
		{
			struct sItem aux = lista->items[esq];
			lista->items[esq] = lista->items[dir];
			lista->items[dir] = aux;
			(*trocas)++;
		}
	}
	
	lista->items[inicio] = lista->items[dir];
	lista->items[dir] = pivo;
	(*trocas)++;
	
	return dir;
}
