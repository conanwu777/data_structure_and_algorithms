#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "header.h"

int carPosition(unsigned int parkingRow)
{
	int ret = 0;
	unsigned int i = 1;
	while (i < parkingRow)
	{
		i *= 2;
		ret++;
	}
	if (i == parkingRow)
		return ret;
	return -1;
}
