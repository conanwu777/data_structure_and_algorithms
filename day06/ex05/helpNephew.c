#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "header.h"

double	die(int nStairs, int nPunch, int nephewStair)
{
	if (nPunch == 0)
		return 0;
	double prob = (double)nephewStair / (double)nStairs;
	for (int i = nephewStair; i < nStairs; i++)
		prob += die(i, nPunch - 1, nephewStair) / (double)nStairs;
	return prob;
}

double	probaNephewWillLive(int nStairs, int nPunch, int nephewStair)
{
	if (nephewStair >= nStairs - 1)
		return 1.0;
	return (1 - die(nStairs, nPunch, nephewStair + 1));
}
