#pragma once
#include "includes.h"

unsigned int quickSort(struct sList* lista);
unsigned int QuickSort(struct sList* lista, int inicio, int fim);
int particiona(struct sList *lista, int inicio, int fim, unsigned int *trocas);
