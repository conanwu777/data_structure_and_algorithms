#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "header.h"

char *resolveNeg(char *s)
{
	if (s[0] == '~')
	{
		for (int i = 0; i < 4; i++)
			s[i] = (s[i + 1] == '0' ? '1' : '0');
		s[4] = 0;
	}
	return (s);
}

char *getAnd(char *a, char *b)
{
	a = resolveNeg(a);
	b = resolveNeg(b);
	for (int n = 0; n < 4; n++)
	{
		if (a[n] != '0' && b[n] != '0')
			a[n] = '1';
		else
			a[n] = '0';
	}
	return a;
}

char *getOr(char *a, char *b)
{
	a = resolveNeg(a);
	b = resolveNeg(b);
	for (int n = 0; n < 4; n++)
	{
		if (a[n] != '0' || b[n] != '0')
			a[n] = '1';
		else
			a[n] = '0';
	}
	return a;
}

int toInt(char *bits)
{
	int ret = 0;

	for (int i = 0; i < 4; i++)
	{
		ret += bits[i] - '0';
		if (i != 3)
			ret <<= 1;
	}
	return ret;
}
