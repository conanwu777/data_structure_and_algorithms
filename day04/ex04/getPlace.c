#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "header.h"

int getPlace(unsigned int parkingRow, int pos)
{
	return (parkingRow & (1 << pos));
}
