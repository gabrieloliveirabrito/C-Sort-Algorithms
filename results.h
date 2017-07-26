#pragma once

typedef struct sResult
{
	double seqTime, searchTime, sortTime;
	int sComp, bComp, t;
	unsigned int trocas;
} Results;
