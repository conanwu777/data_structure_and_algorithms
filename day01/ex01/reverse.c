#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "header.h"

void recurse(struct s_node *lst, char c)
{
	if (!lst->next)
		printf("%s", lst->word);
	else
	{
		recurse(lst->next, 0);
		printf(" %s", lst->word);
	}
	if (c)
		printf("\n");
}

void printReverse(struct s_node *lst)
{
	recurse(lst, 1);
}
