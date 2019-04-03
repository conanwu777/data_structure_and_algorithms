#include "header.h"
#include <stdio.h>
#include <stdlib.h>

double bestPrice(int pizzaSize, double *prices)
{
	double max = 0;

	for (int i = 1; i <= pizzaSize; i++)
	{
		double t = bestPrice(pizzaSize - i, prices);
		t += prices[i];
		if (t > max)
			max = t;
	}
	return max;
}
