#pragma once
#include "includes.h"

struct {
	int n;
} randReg;

struct {
	struct timespec start, end;
} timer;

int random(int min, int max);
int percentage(int current, int total);
void iniciaTimer();
double paraTimer();
