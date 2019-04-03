#include <stdio.h> //printf, scanf, ...
#include <string.h> //memcpy, strlen, ...
#include <unistd.h> //fork, write, sleep...
#include <stdlib.h> //malloc, free, exit...

#include "header.h"

int main(void)
{
	struct s_tank *tank = initTank();

	/*-------------------
	launch your test here
	--------------------*/
	for (int i = 100; i >= 10; i--)
	{
		tankPush(tank, i);
		printf("%d energy added into stack %d, which contains total of %d\n",
			i, tank->n - 1, tank->stacks[tank->n - 1]->sum);

	}
	for (int i = 0; i < tank->n; i++)
	{
		printf("Tank stack %i contains total energy %i\n",
			i, tank->stacks[i]->sum);
	}
	for (int i = 0; i < 103; i++)
		printf("%d popped from tank, now contain %d stacks\n",
			tankPop(tank), tank->n);
	return (0);
}

// Function used for the test
// Don't go further :)
