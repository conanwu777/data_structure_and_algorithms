#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "header.h"

struct s_node *cloneGameBoard(struct s_node *node)
{
	struct s_node *ret;
	struct s_node *t;
	struct s_node *n;
	struct s_node *n2;
	struct s_node *t2;

	if (!node)
		return (NULL);
	ret = (struct s_node*)malloc(sizeof(struct s_node));
	t = ret;
	n = node;
	while (n)
	{
		t->value = n->value;
		if (n->next)
		{
			t->next = (struct s_node*)malloc(sizeof(struct s_node));
			t = t->next;
			n = n->next;
		}
		else
			n = NULL;
	}
	t->next = NULL;
	n = node;
	t = ret;
	while (n)
	{
		t->random = NULL;
		if (n->random)
		{
			n2 = node;
			t2 = ret;
			while (n2)
			{
				if (n->random == n2)
				{
					t->random = t2;
					break ;
				}
				n2 = n2->next;
				t2 = t2->next;
			}
		}
		n = n->next;
		t = t->next;
	}
	return (ret);
}
