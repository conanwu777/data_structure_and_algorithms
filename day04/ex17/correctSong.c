#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "header.h"

void	correctSong(struct s_bit *bit, int l, int row, int col, int dist)
{
	for (int pos = 0; pos < (bit->n << 5); pos++)
		if (pos % l == col && pos / l >= row && pos / l < row + dist)
			bit->arr[pos >> 5] |= (1 << (pos & 31));
}
