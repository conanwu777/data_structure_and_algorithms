#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "header.h"

void free_nodes(struct s_node *lv, struct s_node *nxl)
{
	struct s_node *t;

	while (lv)
	{
		t = lv->next;
		free(lv);
		lv = t;
	}
	while (nxl)
	{
		t = nxl->next;
		free(nxl);
		nxl = t;
	}
}

int	minimumMoves(struct s_node *begin)
{
	struct s_node *t = begin;
	struct s_node *end = begin;
	struct s_node *lvp;
	struct s_node *nxp;
	int level = 1;

	if (!begin)
		return (-1);
	while (end->next)
		end = end->next;
	if (begin == end)
		return (0);
	struct s_node *lv = malloc(sizeof(struct s_node));
	lv->random = begin;
	lv->next = NULL;
	while (1)
	{
		lvp = lv;
		struct s_node *nxl = malloc(sizeof(struct s_node));
		bzero(nxl, sizeof(struct s_node));
		while (lvp && lvp->random)
		{
			if ((lvp->random->random && lvp->random->random == end)
				|| (lvp->random->next && lvp->random->next == end))
			{
				free_nodes(lvp, nxl);
				return (level);
			}
			if (lvp->random->random)
			{
				nxp = malloc(sizeof(struct s_node));
				nxp->random = lvp->random->random;
				nxp->next = nxl;
				nxl = nxp;
			}
			if (lvp->random->next)
			{
				nxp = malloc(sizeof(struct s_node));
				nxp->random = lvp->random->next;
				nxp->next = nxl;
				nxl = nxp;
			}
			t = lvp;
			lvp = lvp->next;
			free(t);
		}
		lv = nxl;
		level++;
	}
	return (-1);
}