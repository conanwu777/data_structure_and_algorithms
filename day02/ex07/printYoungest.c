#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include "header.h"

int find_youngest(int *ages, int length)
{
	if (length < 1)
		return (170000);
	if (length == 1)
		return ages[0];
	int m = length / 2;
	int l = find_youngest(ages, m);
	int r = find_youngest(&ages[m], length - m);
	return (l < r ? l : r);
}

void printYoungest(int *ages, int length)
{
	int n;
	if ((n = find_youngest(ages, length)) == 170000)
		printf("Wrong input\n");
	printf("Youngest : %d\n", n);
}
