#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "header.h"

int rightmostCar(unsigned int parkingRow)
{
	if (parkingRow)
	{
		int i = 0;
		while (!(parkingRow & 1))
		{
			parkingRow >>= 1;
			i++;
		}
		return i;
	}
	return -1;
}
