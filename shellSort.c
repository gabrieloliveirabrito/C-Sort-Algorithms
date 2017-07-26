#include "shellSort.h"

//Algorítmo shell sort
unsigned int shellSort(struct sList* lista)
{
	int k = 3, i, j, h = 1;
	unsigned int trocas = 0;
	
	while(h <= lista->total)
		h = k * h + 1;
		
	while (h != 1)
	{
		h /= k;
		
		for(i = h; i < lista->total; i++)
		{
			struct sItem aux = lista->items[i];
			j = i - h;
			
			while(j >= 0 && aux.chave < lista->items[j].chave)
			{
				trocas++;
				lista->items[j + h] = lista->items[j];
				j -= h;
			}
			lista->items[j + h] = aux;
		}
	}
	
	return trocas;
}
