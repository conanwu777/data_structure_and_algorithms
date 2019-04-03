#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "header.h"

char *getXor(char *a, char *b)
{
	for (int n = 0; n < 6; n++)
	{
		if ((a[n] != '0' || b[n] != '0')
			&& !(a[n] != '0' && b[n] != '0'))
			a[n] = '1';
		else
			a[n] = '0';
	}
	return a;
}

int toInt(char *bits)
{
	int ret = 0;

	for (int i = 0; i < 6; i++)
	{
		ret += bits[i] - '0';
		if (i != 5)
			ret <<= 1;
	}
	return ret;
}
