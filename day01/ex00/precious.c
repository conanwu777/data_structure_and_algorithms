#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "header.h"

struct s_node *make_machine(void)
{
	char *al = CS;
	int l = strlen(al);
	struct s_node *node;
	struct s_node *t;

	node = (struct s_node*)malloc(sizeof(struct s_node));
	bzero(node, sizeof(struct s_node));
	node->c = al[0];
	for (int i = 1; i < l; i++)
	{
		t = (struct s_node*)malloc(sizeof(struct s_node));
		t->c = al[i];
		node->next = t;
		t->prev = node;
		node = t;
	}
	while (t->prev)
		t = t->prev;
	node->next = t;
	t->prev = node;
	node = t;
	return (node);
}

char *precious(int *text, int size)
{
	char *ret;
	struct s_node *node;
	node = make_machine();
	ret = (char*)malloc(size + 1);
	int i;
	for (i = 0; i < size; i++)
	{
		if (text[i] >= 0)
			for (int j = 0; j < text[i]; j++)
				node = node->next;
		else
			for (int j = 0; j > text[i]; j--)
				node = node->prev;
		ret[i] = node->c;
	}
	ret[i] = 0;
	char *al = CS;
	int l = strlen(al);
	struct s_node *t;
	t = node;
	for (int i = 0; i < l; i++)
	{
		node = node->next;
		free(t);
		t = node;
	}
	return (ret);
}
