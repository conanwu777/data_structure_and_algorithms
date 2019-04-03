#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "header.h"

int		countArts(struct s_art **arts)
{
	int i = 0;
	while (*arts)
	{
		arts++;
		i++;
	}
	return (i);
}

void	sort_recur(struct s_art **arts, int n)
{
	if (n <= 1)
		return ;
	int Ppos = n - 1;
	struct s_art *t = (struct s_art*)malloc(sizeof(struct s_art));
	*t = *(arts[n / 2]);
	*(arts[n / 2]) = *(arts[Ppos]);
	*(arts[Ppos]) = *t;
	for (int i = 0; i < Ppos; i++)
		if (strcmp(arts[i]->name, t->name) > 0)
		{
			*(arts[Ppos]) = *(arts[i]);
			if (Ppos > i + 1)
			{
				Ppos--;
				*(arts[i]) = *(arts[Ppos]);
				*(arts[Ppos]) = *t;
				i--;
			}
			else
			{
				*(arts[i]) = *t;
				Ppos = i;
				break ;
			}
		}
	sort_recur(arts, Ppos);
	sort_recur(arts + Ppos + 1, n - Ppos - 1);
	free(t);
}

void	sortArts(struct s_art **arts)
{
	sort_recur(arts, countArts(arts));
}

int	searchPrice(struct s_art **arts, int n, char *name)
{
	int k;

	if (n / 2 == 0)
		return (strcmp(arts[0]->name, name) ? -1 : arts[0]->price);
	if (!(k = strcmp((arts[n / 2])->name, name)))
		return (arts[n / 2]->price);
	if (k > 0)
		return (searchPrice(arts, n / 2, name));
	return (searchPrice(arts + n / 2, n - n / 2, name));
}
