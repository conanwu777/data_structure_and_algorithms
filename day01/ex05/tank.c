#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "header.h"

struct s_tank *initTank(void)
{
	struct s_tank *tank = (struct s_tank*)malloc(sizeof(struct s_tank));
	tank->n = 1;
	tank->stacks = (struct s_stack **)malloc(sizeof(struct s_stack *));
	tank->stacks[0] = (struct s_stack*)malloc(sizeof(struct s_stack));
	bzero(tank->stacks[0], sizeof(struct s_stack));
	return (tank);
}

void tankPush(struct s_tank *tank, int energy)
{
	if (!tank || !tank->stacks || !tank->stacks[0] || energy < 10 || energy > 100)
		return ;
	struct s_elem *t = (struct s_elem*)malloc(sizeof(struct s_elem));
	t->energy = energy;
	t->next = tank->stacks[tank->n - 1]->elem;
	if (energy + tank->stacks[tank->n - 1]->sum > 1000)
	{
		tank->stacks = realloc(tank->stacks, sizeof(struct s_stack*) * (tank->n + 1));
		tank->stacks[tank->n] = (struct s_stack*)malloc(sizeof(struct s_stack));
		tank->stacks[tank->n]->sum = 0;
		tank->n++;
	}
	tank->stacks[tank->n - 1]->elem = t;
	tank->stacks[tank->n - 1]->sum += energy;
}

int tankPop(struct s_tank *tank)
{
	if (!tank || !tank->stacks || !tank->stacks[0] || !tank->stacks[0]->elem)
		return (0);
	int eng = tank->stacks[tank->n - 1]->elem->energy;
	struct s_elem *t;
	if (!(t = tank->stacks[tank->n - 1]->elem))
		return (0);
	if (tank->stacks[tank->n - 1]->sum > eng)
	{
		tank->stacks[tank->n - 1]->sum -= eng;
		tank->stacks[tank->n - 1]->elem = t->next;
		free(t);
	}
	else
	{
		free(t);
		if (tank->n > 1)
		{
			free(tank->stacks[tank->n - 1]);
			tank->n--;
			tank->stacks = realloc(tank->stacks, sizeof(struct s_stack*) * (tank->n + 1));
		}
		if (tank->n == 1 && tank->stacks[0]->sum == eng)
			bzero(tank->stacks[0], sizeof(struct s_stack));
	}
	return (eng);
}
