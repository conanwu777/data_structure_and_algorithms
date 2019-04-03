#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "header.h"

double probaDistance(int dist, int *locations, int n)
{
	int count = 0;
	for (int i = 0; i < n - 1; i++)
	{
		int j = i;
		while (j < n && locations[j] - locations[i] <= dist)
			j++;
		count += j - i - 1;
	}
	double prob = (double)count * 2 / n / (n - 1);
	return (1 - prob);
}
