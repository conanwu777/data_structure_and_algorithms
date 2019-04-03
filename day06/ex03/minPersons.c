#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "header.h"

int		minPersons(int elements, int minPercentage)
{
	int ret = 1;
	if (minPercentage > 100)
		minPercentage = 100;
	double prob = 0;
	while (prob < (double)minPercentage / 100.0)
	{
		prob += (1.0 - prob) * (double)ret / (double)elements;
		ret++;
	}
	return ret;
}