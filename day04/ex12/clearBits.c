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

unsigned int clearBits(unsigned int parkingRow, int n)
{
	return (parkingRow & (~subtract((1 << n), 1)));
}
