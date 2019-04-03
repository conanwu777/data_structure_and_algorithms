#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "header.h"

typedef struct s_art t_art;

void placeTop(t_art **arts, int pos, int n)
{
	int t;
	int i = pos;
	while (i < n && (
		((i << 1) + 1 < n && strcmp(arts[i]->name, arts[(i << 1) + 1]->name) < 0)
		|| ((i << 1) + 2 < n && strcmp(arts[i]->name, arts[(i << 1) + 2]->name) < 0)))
	{
		if ((i << 1) + 2 >= n)
			t = (i << 1) + 1;
		else
			t = (strcmp(arts[(i << 1) + 1]->name, arts[(i << 1) + 2]->name) < 0 ?
				(i << 1) + 2 : (i << 1) + 1);
		t_art *tmp = arts[t];
		arts[t] = arts[i];
		arts[i] = tmp;
		i = t;
	}
}

void maxHeapify(t_art **arts, int n)
{
	for (int i = 1; i < n; i++)
		if (strcmp(arts[(i - 1) >> 1]->name, arts[i]->name) < 0)
		{
			int j = i;
			while ((j - 1) >> 1 >= 0 && strcmp(arts[(j - 1) >> 1]->name, arts[j]->name) < 0)
			{
				t_art *tmp = arts[j];
				arts[j] = arts[(j - 1) >> 1];
				arts[(j - 1) >> 1] = tmp;
				j = (j - 1) >> 1;
			}
		}
}

void heapSort(struct s_art **arts, int n)
{
	maxHeapify(arts, n);
	t_art *tmp;
	for (int pos = n - 1; pos > 0; pos--)
	{
		tmp = arts[0];
		arts[0] = arts[pos];
		arts[pos] = tmp;
		placeTop(arts, 0, pos);
	}
}
