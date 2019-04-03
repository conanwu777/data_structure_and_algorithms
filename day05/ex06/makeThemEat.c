#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_people t_people;

int fillTable(t_people **tmp, t_people **rem, t_people **p, int n, int count)
{
	int c[2] = {0, 0};
	n <<= 1;
	for (int i = 0; i < count && (n >>= 1) <= (1 << count); i++)
		if (n & 1)
			tmp[c[0]++] = p[i];
		else
			rem[c[1]++] = p[i];
	tmp[c[0]] = NULL, rem[c[1]] = NULL;
	return 1;
}

int isPossible(struct s_people **people, int nbTable, int tT)
{
	int count[2] = {0, 0};
	for (count[0] = 0; people[count[0]]; count[0]++)
		count[1] += people[count[0]]->time;
	if (nbTable == 1)
		return (count[1] <= tT ? 1 : 0);
	t_people *tmp[count[0] + 1];
	t_people *rem[count[0] + 1];
	for (unsigned int i = 0; i <= (1 << count[0])
		&& fillTable(tmp, rem, people, i, count[0]); i++)
		if (isPossible(tmp, 1, tT) && isPossible(rem, nbTable - 1, tT))
			return 1;
	return 0;
}
