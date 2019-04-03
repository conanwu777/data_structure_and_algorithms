#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "header.h"

unsigned int add(unsigned int a, unsigned int b)
{
	if (b)
		return add(a ^ b, (a & b) << 1);
	return a;
}

int isFilled(unsigned int parkingRow)
{
	if (parkingRow & add(parkingRow, 1))
		return 0;
	return 1;
}
