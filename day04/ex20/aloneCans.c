#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "header.h"

void aloneCans(int *arr, int n)
{
	int ret = 0;
	for (int i = 0; i < n; i++)
		ret ^= arr[i];
	int b = 1;
	while ((ret - 1) ^ b)
		b <<= 1;
	int num1 = 0;
	int num2 = 0;
	for (int i = 0; i < n; i++)
		if (arr[i] & b)
			num1 ^= arr[i];
		else
			num2 ^= arr[i];
	printf("%d\n%d\n", num1, num2);
}
