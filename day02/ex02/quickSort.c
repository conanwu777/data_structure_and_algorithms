 #include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include "header.h"

typedef struct s_player t_player;

void	sort_recur(struct s_player **players, int n)
{
	if (n <= 1)
		return ;
	int Ppos = n - 1;
	t_player *t = malloc(sizeof(t_player));
	*t = *(players[n / 2]);
	*(players[n / 2]) = *(players[Ppos]);
	*(players[Ppos]) = *t;
	for (int i = 0; i < Ppos; i++)
		if (players[i]->score < t->score)
		{
			*(players[Ppos]) = *(players[i]);
			if (Ppos > i + 1)
			{
				Ppos--;
				*(players[i]) = *(players[Ppos]);
				*(players[Ppos]) = *t;
				i--;
			}
			else
			{
				*(players[i]) = *t;
				Ppos = i;
				break ;
			}
		}
	sort_recur(players, Ppos);
	sort_recur(players + Ppos + 1, n - Ppos - 1);
	free(t);
}

void quickSort(struct s_player **players)
{
	int size = 0;

	while (players[size])
		size++;
	sort_recur(players, size);
}
