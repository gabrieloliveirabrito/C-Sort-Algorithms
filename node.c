#include "node.h"

int percorreNo(Node* no)
{
	if(no->proximo != NULL)
	{
		no = no->proximo;
		return 1;
	}
	else
		return 0;
}
