#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "header.h"

int subtract(int a, int b)
{
	if (b)
		return subtract(a ^ b, (~a & b) << 1);
	return a;
}

int leftmostCar(unsigned int parkingRow)
{
	int i = 0;
	while (parkingRow)
	{
		parkingRow >>= 1;
		i++;
	}
	return (subtract(i, 1));
}
