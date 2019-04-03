#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include "header.h"

typedef struct s_player t_player;

void merge_recur(t_player **players, t_player **arr, int n)
{
	if (n / 2 > 1)
	{
		merge_recur(players, arr, n / 2);
		merge_recur(&players[n / 2], &arr[n / 2], n - n / 2);
	}
	int c = 0;
	int c2 = n / 2;
	for (int i = 0; i < n; i++)
	{
		if (c == -1 || c2 == -1)
		{
			arr[i] = (c == -1 ? players[c2++] : players[c++]);
			continue ;
		}
		if (players[c]->score >= players[c2]->score)
		{
			arr[i] = players[c];
			c = (c + 1 >= n / 2 ? -1 : c + 1);
		}
		else
		{
			arr[i] = players[c2];
			c2 = (c2 + 1 >= n ? -1 : c2 + 1);
		}
	}
	for (int i = 0; i < n; i++)
		players[i] = arr[i];
}

struct s_player **mergeSort(struct s_player **players)
{
	int size = 0;

	while (players[size])
		size++;

	t_player **arr = malloc(sizeof(t_player*) * (size + 1));
	merge_recur(players, arr, size);
	free(arr);
	return (players);
}
