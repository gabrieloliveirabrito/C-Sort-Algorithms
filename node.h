#pragma once
#include "item.h"

typedef struct Node
{
	Item item;
	struct Node *anterior, *proximo;
} Node;

int percorreNo(Node* sentinela, Node* proximo);
