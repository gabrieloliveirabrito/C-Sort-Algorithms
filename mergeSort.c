#include "mergeSort.h"

unsigned int merge(struct sList *lista, int p, int q, int r)
{
	int n1 = q - p + 1, n2 = r - q;
	int i, j, k;
	int trocas = 0;
	
	struct sList E, D;
	criaLista(&E, n1 + 1);
	criaLista(&D, n2 + 1);
		
	for(i = 0; i < n1; i++)
		adicionar(&E, lista->items[p + i]);
		
	for(i = 0; i < n2; i++)
		adicionar(&D, lista->items[q + i + 1]);
	
	E.items[n1].chave = D.items[n2].chave = INT_MAX;
	i = j = 0;
	
	for(k = p; k <= r; k++)
	{
		if(E.items[i].chave <= D.items[j].chave)
		{
			lista->items[k] = E.items[i];
			i++;
			trocas++;
		}
		else
		{
			lista->items[k] = D.items[j];
			j++;
			trocas++;
		}
	}
	
	desaloca(&E);
	desaloca(&D);
	
	return trocas;
}

unsigned int MergeSort(struct sList *lista, int p, int r)
{
	unsigned int trocas = 0;
	if(p < r)
	{
		int q = (p + r) / 2;
		trocas += MergeSort(lista, p, q);
		trocas += MergeSort(lista, q+1, r);
		trocas += merge(lista, p, q, r);
	}
}

unsigned int mergeSort(struct sList *lista)
{
	return MergeSort(lista, 0, lista->total - 1);
}
