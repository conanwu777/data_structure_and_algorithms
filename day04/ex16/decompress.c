#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "header.h"

int	**pianoDecompress(struct s_bit *bit, int l)
{
	int **ret = calloc((bit->n << 5) / l + 1, sizeof(int*));
	for (int i = 0; i <= (bit->n << 5) / l; i++)
		ret[i] = calloc(l, sizeof(int));
	int num = 0;
	int count = 0;
	for (int pos = 0; pos < (bit->n << 5); pos++)
	{
		ret[pos / l][pos % l] = bit->arr[num] & 1;
		bit->arr[num] >>= 1;
		count++;
		if (count & (1 << 5))
		{
			count = 0;
			num++;
		}
		if (num == bit->n)
			break ;
	}
	ret[((bit->n << 5) + l - 1) / l] = NULL;
	return ret;
}
