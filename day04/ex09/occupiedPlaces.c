#include "header.h"

int subtract(int a, int b)
{
	if (b)
		return subtract(a ^ b, (~a & b) << 1);
	return a;
}

//I assume when loops are allowed, we can use a counter and increment it
//I can use the add function from ex08 but that will break the O(m) time

int occupiedPlaces(unsigned int parkingRow)
{
	int ret = 0;
	while (parkingRow)
	{
		parkingRow &= subtract(parkingRow, 1);
		ret++;
	}
	return ret;
}
