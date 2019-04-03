#include "header.h"
#include <stdio.h>
#include <stdlib.h>

double opt_recur(double *optPrice, int size, double *price)
{
	optPrice[size] = price[size];
	for (int i = 1; i < size; i++)
	{
		if (!optPrice[i])
			opt_recur(optPrice, i, price);
		double t = optPrice[i] + price[size - i];
		if (t > optPrice[size])
			optPrice[size] = t;
	}
	return optPrice[size];
}

double optimizedBestPrice(int pizzaSize, double *prices)
{
	if (pizzaSize == 0)
		return 0;
	double *optPrice = calloc(pizzaSize, sizeof(double));
	optPrice[1] = prices[1];
	double ret = opt_recur(optPrice, pizzaSize, prices);
	free(optPrice);
	return ret;
}
