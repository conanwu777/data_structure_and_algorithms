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

int carPosition(unsigned int parkingRow)
{
	int i = 0;

	if (parkingRow)
	{
		if (parkingRow & subtract(parkingRow, 1))
			return -1;
		while (parkingRow)
		{
			parkingRow >>= 1;
			i++;
		}
		return subtract(i, 1);
	}
	return -1;
}
