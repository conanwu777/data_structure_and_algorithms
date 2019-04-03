#include <stdio.h> //printf, scanf, ...
#include <string.h> //memcpy, strlen, ...
#include <unistd.h> //fork, write, sleep...
#include <stdlib.h> //malloc, free, exit...

#include "header.h"

int main(int ac, char **av)
{
	struct s_max *res;
	int n;
	int k = 4;
	if (ac >= 2)
	{
		n = ac - 1;
		int arr[n];
		for (int i = 1; i < ac; i++)
			arr[i - 1] = atoi(av[i]);
		for (int i = 0; i < n; i++)
			printf("%d ", arr[i]);
		printf("\n");

		res = maxSlidingWindow(arr, n, k);
		if (res) {
			for (int i = 0; i < res->length; i++)
				printf("%d ", res->max[i]);
			printf("\n");
		}
	}
	else
	{
		n = 10;
		int arr[] = {10, -2, 2, 21, -5, 42, 3, -6, 17, 11};
		res = NULL;
		for (int i = 0; i < n; i++)
			printf("%d ", arr[i]);
		printf("\n");

		res = maxSlidingWindow(arr, n, k);
		if (res) {
			for (int i = 0; i < res->length; i++)
				printf("%d ", res->max[i]);
			printf("\n");
		}
	}
	return (0);
}

// Function used for the test
// Don't go further :)

