#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "header.h"

unsigned int clearPlace(unsigned int parkingRow, int pos)
{
	if (parkingRow & (1 << pos))
		return parkingRow & (~(1 << pos));
	return parkingRow;
}
