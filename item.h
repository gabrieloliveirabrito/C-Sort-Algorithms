#pragma once
#include "includes.h"

struct sItem
{
	Chave chave;
	char strings[10][100];
	double reais[5];
};

struct sItem copiaItem(struct sItem B);
