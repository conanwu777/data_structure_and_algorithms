#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include "header.h"

typedef struct s_node t_node;

t_node **getpath(t_node *root, char *target)
{
	t_node **p;
	if (!strcmp(root->name, target))
	{
		p = malloc((sizeof(t_node*) * 2));
		p[0] = root;
		p[1] = NULL;
		return p;
	}
	for (int i = 0; root->children[i]; i++)
	{
		if ((p = getpath(root->children[i], target)))
		{
			int len = 0;
			while (p[len])
				len++;
			p = realloc(p, sizeof(t_node*) * (len + 2));
			p[len] = root;
			p[len + 1] = NULL;
			return p;
		}
	}
	return NULL;
}

t_node *findParent(t_node *root, char *firstSpecies, char *secondSpecies)
{
	t_node **p1 = getpath(root, firstSpecies);
	t_node **p2 = getpath(root, secondSpecies);
	t_node *res = NULL;

	if (p1 && p2)
	{
		int l1 = 0;
		while (p1[l1])
			l1++;
		int cmp = l1;
		int l2 = 0;
		while (p2[l2])
			l2++;	
		while (l1 >= 0 && l2 >= 0 && p1[l1] == p2[l2])
		{
			l1--;
			l2--;
		}
		if (l1 < cmp)
			res = p1[l1 + 1];
	}
	if (p1)
		free(p1);
	if (p2)
		free(p2);
	return (res);
}
