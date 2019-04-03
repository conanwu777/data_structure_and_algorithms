#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "header.h"

unsigned int updatePlace(unsigned int parkingRow, int pos, int value)
{
	if (value)
		return (parkingRow & (~(1 << pos))) | (1 << pos);
	return ((parkingRow ^ (1 << pos)) & parkingRow);
}
