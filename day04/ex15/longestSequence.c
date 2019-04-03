#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "header.h"

int longestSequence(unsigned int parkingRow)
{
	int count = 0;
	while (parkingRow)
	{
		parkingRow &= (parkingRow >> 1);
		count++;
	}
	return count;
}
