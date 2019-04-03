#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include "header.h"

void countSort(unsigned char *utensils, int n)
{
	unsigned char max = 0;

	for (int i = 0; i < n; i++)
	{
		if (utensils[i] > max)
			max = utensils[i];
	}
	int *arr = malloc(sizeof(int) * (max + 1));
	bzero(arr, sizeof(int) * (max + 1));
	for (int j = 0; j < n; j++)
		arr[utensils[j]]++;
	int pos = 0;
	for (unsigned char i = 0; i <= max; i++)
		while (arr[i])
		{
			utensils[pos] = i;
			pos++;
			arr[i]--;
		}
	free(arr);
}
