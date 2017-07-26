#include "list.h"

void criaLista(struct sList *list, int tamanho)
{
	list->total = 0;
	list->tamanho = tamanho;
	
	list->items = (struct sItem*)calloc(tamanho, sizeof(struct sItem));
}

void desaloca(struct sList *list)
{
	free(list->items);
}

void adicionar(struct sList *list, struct sItem item)
{
	/*Node* no = ultimoNo(List);
	no->proximo = (Node*)malloc(sizeof(Node));
	no->proximo->item = item;*/
	
	list->items[list->total] = item;
	list->total++;
}

//Copia os items de uma lista para a outra, alterando os itens caso existente
void copia(struct sList *from, struct sList* to)
{
	criaLista(to, from->tamanho);
	
	int i;
	for(i = 0; i < from->tamanho; i++)
		adicionar(to, from->items[i]);
}

void copiaN(struct sList *from, struct sList* to, int total)
{
	int t = total > from->tamanho ? from->tamanho : total;
	criaLista(to, t);
	
	int i;
	for(i = 0; i < t; i++)
		adicionar(to, from->items[i]);
}
