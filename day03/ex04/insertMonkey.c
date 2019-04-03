#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include "header.h"

typedef struct s_node t_node;

int countNodes(t_node *root)
{
	if (!root)
		return 0;
	return (countNodes(root->left) + 1 + countNodes(root->right));
}

int findLargestbit(int n)
{
	int i;
	for (i = 1; i <= n; i <<= 1)
		;
	i >>= 1;
	return (i);
}

void swap(t_node **root, t_node *parent, t_node **me, t_node **monkey)
{
	t_node *tmp = *me;
	t_node *tmp2 = *monkey;
	if (!parent)
	{
		(*monkey)->left = (*root)->left;
		(*monkey)->right = (*root)->right;
		*root = *monkey;
		*me = *monkey;
		*monkey = tmp;
		return ;
	}
	if (parent->left == *me)
		parent->left = *monkey;
	else
		parent->right = *monkey;
	(*monkey)->left = (*me)->left;
	(*monkey)->right = (*me)->right;
	*monkey = tmp;
	*me = tmp2;
}

void insertMonkey(struct s_node **root, struct s_node *monkey)
{
	if (!*root)
	{
		*root = monkey;
		return ;
	}
	int size = countNodes(*root);
	size++;
	int i = findLargestbit(size);
	i >>= 1;
	t_node *t = *root;
	t_node *parent = NULL;
	while (i > 1)
	{
		if (t->value > monkey->value)
			swap(root, parent, &t, &monkey);
		parent = t;
		if (size & i)
			t = t->right;
		else
			t = t->left;
		i >>= 1;
	}
	if (t->value > monkey->value)
		swap(root, parent, &t, &monkey);
	if (size & 1)
		t->right = monkey;
	else
		t->left = monkey;
	monkey->left = NULL;
	monkey->right = NULL;
}
