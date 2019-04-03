#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "header.h"

int howManyJesus(char *bible, char *jesus)
{
	int r = 0;
	int n = strlen(bible);
	int m = strlen(jesus);
	size_t max = 127;
	size_t j = (size_t)jesus[0];
	if (m > n)
		return (0);
	size_t hash = (size_t)bible[0];
	for (int i = 1; i < m; i++)
	{
		hash <<= 7;
		hash += (size_t)bible[i];
		if (i < 8)
		{
			max <<= 7;
			max += 127;
		}
		j <<= 7;
		j += (size_t)jesus[i];
	}
	if (hash == j && !strncmp(bible, jesus, m))
		r++;
	for (int i = m; i < n; i++)
	{
		hash <<= 7;
		hash = hash & max;
		hash += (size_t)bible[i];
		if (hash == j && !strncmp(&bible[i - m + 1], jesus, m))
			r++;
	}
	return r;
}
