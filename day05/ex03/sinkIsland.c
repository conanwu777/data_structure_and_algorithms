#include "header.h"
#include <stdio.h>
#include <stdlib.h>

void sinkIsland(int **map, int row, int col)
{
	if (map[row][col] == 0)
		return ;
	map[row][col] = 0;
	if (row > 0 && map[row - 1][col])
		sinkIsland(map, row - 1, col);
	if (map[row + 1] && map[row + 1][col])
		sinkIsland(map, row + 1, col);
	if (col > 0 && map[row][col- 1])
		sinkIsland(map, row, col - 1);
	if (map[row][col + 1] > 0)
		sinkIsland(map, row, col + 1);
}