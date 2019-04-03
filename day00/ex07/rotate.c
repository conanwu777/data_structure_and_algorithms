#include "header.h"

void rotate(int **picture, int n)
{
	int t;

	for (int j = 0; j < n / 2; j++)
	{
		for (int i = 0; i < n / 2; i++)
		{
			t = picture[i][j];
			picture[i][j] = picture[n - 1 - j][i];
			picture[n - 1 - j][i] = picture[n - 1 - i][n - 1 - j];
			picture[n - 1 - i][n - 1 - j] = picture[j][n - 1 - i];
			picture[j][n - 1 - i] = t;
		}
	}
}
