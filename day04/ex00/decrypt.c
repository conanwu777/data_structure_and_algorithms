#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "header.h"

char *getSum(char *a, char *b)
{
	char carry = 0;

	for (int n = 5; n >= 0; n--)
	{
		char A = a[n] - '0';
		char B = b[n] - '0';
		if (A & B)
		{
			a[n] = carry + '0';
			carry = 1;
		}
		else if (A ^ B)
			a[n] = !carry + '0';
		else
		{
			a[n] = carry + '0';
			carry = 0;
		}
	}
	return (a);
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
