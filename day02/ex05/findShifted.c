#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include "header.h"

int findstart(int *rocks, int length)
{
	int r;
	int r2;

	if (length == 1 || rocks[0] < rocks[length - 1])
		return (0);
	if (length == 2)
		return (rocks[0] <= rocks[1] ? 0 : 1);
	int m = length / 2;
	if (rocks[0] > rocks[m])
		return (findstart(rocks, m + 1));
	if (rocks[m] > rocks[length - 1])
		return (m + findstart(&rocks[m], length - m));
	r = findstart(rocks, m);
	r2 = findstart(&rocks[m], length - m);
	return (rocks[r] < rocks[r2] ? r : m + r2);
}

int	searchShifted(int *rocks, int length, int value)
{
	if (length == 0)
		return -1;
	if (length == 1)
		return (rocks[0] == value ? 0 : -1);
	int st = findstart(rocks, length);
	int m;
	int t;
	int l = 0;
	int r = length - 1;
	while (l < r)
	{
		m = (l + r) / 2;
		if ((t = rocks[(st + m) % length]) == value)
			return ((st + m) % length);
		if (t < value)
		{
			l = m + 1;
			continue ;
		}
		r = m - 1;
	}
	return -1;
}
