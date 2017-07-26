#include "item.h"

struct sItem copiaItem(struct sItem B)
{
	struct sItem item;
	item.chave = B.chave;
	
	int i;
	for(i = 0; i < 10; i++)
		strcpy(item.strings[i], B.strings[i]);
	for(i = 0; i < 5; i++)
		item.reais[i] = B.reais[i];
		
	return item;
}
