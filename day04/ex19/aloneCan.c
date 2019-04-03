#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "header.h"

void aloneCan(int *arr, int n)
{
	int ret = 0;
	for (int i = 0; i < n; i++)
	{
		ret ^= arr[i];
	}
	printf("%d\n", ret);
}
