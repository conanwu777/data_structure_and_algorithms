#include "header.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct s_array t_array;

void getSlices(t_array *arr, int sizeRemain)
{
	if (sizeRemain == 0)
		arrayPrint(arr);
	else
		for (int i = sizeRemain; i >= 1; i--)
		{
			t_array *tmp = arrayClone(arr);
			arrayAppend(tmp, i);
			getSlices(tmp, sizeRemain - i);
		}
}

void printPossibleSlices(int pizzaSize)
{
	t_array *arr = arrayInit();
	getSlices(arr, pizzaSize);
	free(arr->content);
	free(arr);
}
