#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "header.h"

double probabilityWin(double firstDollarsBet, double dollarsWanted, int nbGame)
{
	if (firstDollarsBet >= dollarsWanted)
		return 1;
	if (nbGame == 0)
		return 0;
	double prob = probabilityWin(firstDollarsBet * 2, dollarsWanted, nbGame - 1) * 18.0 / 37.0;
	prob += probabilityWin(firstDollarsBet / 2, dollarsWanted, nbGame - 1) / 37.0;
	return (prob);
}
