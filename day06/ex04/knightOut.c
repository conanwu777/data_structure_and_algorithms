#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "header.h"

int getInitialPos(uint64_t board)
{
	int pos = -1;
	for (int i = 0; i < 64; i++)
	{
		if (board & 1)
		{
			if (pos == -1)
				pos = i;
			else
				return -1;
		}
		board >>= 1;
	}
	return pos;
}

double probIn(int r, int c, int n, double ***store)
{
	if (r < 0 || r >= 8 || c < 0 || c >= 8)
		return 0;
	if (n == 0)
		return 1;
	if (store[n][r][c] >= 0)
		return (store[n][r][c]);
	int mvx[8] = {2, 2, -2, -2, 1, 1, -1, -1};
	int mvy[8] = {1, -1, 1, -1, 2, -2, 2, -2};
	double res = 0;
	for (int i = 0; i < 8; i++)
		res += probIn(r + mvy[i], c + mvx[i], n - 1, store) / 8.0;
	store[n][r][c] = res;
	return res;
}

double knightOut(uint64_t board, int n)
{
	if (n > 10000)
		return 1;
	double ***store = calloc(n + 1, sizeof(double**));
	for (int i = 0; i < n + 1; i++)
	{
		store[i] = calloc(8, sizeof(double*));
		for (int j = 0; j < 8; j++)
		{
			store[i][j] = calloc(8, sizeof(double));
			for (int k = 0; k < 8; k++)
				store[i][j][k] = -1;
		}
	}
	int pos = getInitialPos(board);
	int r = pos / 8;
	int c = pos % 8;
	double prob = 1.0 - probIn(r, c, n, store);
	for (int i = 0; i < n + 1; i++)
	{
		for (int j = 0; j < 8; j++)
			free(store[i][j]);
		free(store[i]);
	}
	free(store);
	return (prob);
}
