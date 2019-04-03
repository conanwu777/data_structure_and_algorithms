#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include "header.h"

typedef struct s_stone t_stone;

void sortStones(struct s_stone **stone)
{
	t_stone *t = *stone;
	t_stone tmp;

	int count = 0;
	while (t)
	{
		count++;
		t = t->next;
	}
	t_stone *ds = malloc(sizeof(t_stone) * count);
	bzero(ds, sizeof(t_stone) * count);
	t = *stone;
	ds[0].size = t->size;
	ds[0].next = t;
	int d = 0;
	while (t)
	{
		if (t->size != ds[d].size)
		{
			d++;
			ds[d].size = t->size;
			ds[d].next = t;
		}
		t = t->next;
	}
	for (int j = d; j >= 0; j--)
		for (int i = 0; i < j; i++)
			if (ds[i + 1].size < ds[i].size)
			{
				tmp = ds[i];
				ds[i] = ds[i + 1];
				ds[i + 1] = tmp;
			}
	*stone = ds[0].next;
	t = *stone;
	for (int i = 0; i <= d; i++)
	{
		while (t->next && t->next->size == t->size)
			t = t->next;
		t->next = NULL;
		if (i < d)
		{
			t->next = ds[i + 1].next;
			t = t->next;
		}
	}
	free(ds);
}
