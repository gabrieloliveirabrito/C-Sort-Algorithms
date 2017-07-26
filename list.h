#pragma once
#include "includes.h"

struct sList
{
	int tamanho, total;
	struct sItem *items;
};

void criaLista(struct sList *list, int tamanho);
void desaloca(struct sList *list);
void adicionar(struct sList *list, struct sItem item);
void copia(struct sList *from, struct sList* to);
void copiaN(struct sList *from, struct sList* to, int total);
