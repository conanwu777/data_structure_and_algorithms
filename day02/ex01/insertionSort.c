#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include "header.h"

typedef struct s_player t_player;

void insertionSort(struct s_player **players)
{
	int size = 0;
	t_player *tmp;

	while (players[size])
		size++;
	if (size <= 1)
		return ;
	for (int i = 1; i < size; i++)
	{
		tmp = players[i];
		for (int j = 0; j < i; j++)
			if (tmp->score > players[j]->score)
			{
				memcpy(&players[j + 1], &players[j], sizeof(t_player*) * (i - j));
				players[j] = tmp;
				break ;
			}
	}
}
