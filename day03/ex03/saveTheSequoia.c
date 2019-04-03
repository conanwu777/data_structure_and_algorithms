#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include "header.h"

typedef struct s_node t_node;

t_node *swap(t_node **root, t_node **parent, t_node *me, t_node *ch)
{
	t_node *p = *parent;
	if (p)
	{
		if (p->left == me)
			p->left = ch;
		else
			p->right = ch;
	}
	else
		*root = ch;
	if (me->left == ch)
	{
		me->left = ch->left;
		ch->left = me;
		t_node *tmp = me->right;
		me->right = ch->right;
		ch->right = tmp;
	}
	else
	{
		me->right = ch->right;
		ch->right = me;
		t_node *tmp = me->left;
		me->left = ch->left;
		ch->left = tmp;
	}
	*parent = ch;
	return (me);
}

void	maxHepify(t_node **base, t_node *parent, t_node *root)
{
	if (root->left)
		maxHepify(base, root, root->left);
	if (root->right)
		maxHepify(base, root, root->right);
	t_node *t = root;
	while (t && (t->right || t->left)
		&& ((t->right && t->value < t->right->value)
		|| (t->left && t->value < t->left->value)))
	{
		t_node *tmp;
		if (!t->right || !t->left)
			tmp = (t->left ? t->left : t->right);
		else
			tmp = (t->right->value > t->left->value ? t->right : t->left);
		t = swap(base, &parent, t, tmp);
	}
}

void	saveTheSequoia(struct s_node **root)
{
	if (!root || !(*root) || (!(*root)->left && !(*root)->right))
		return ;
	maxHepify(root, NULL, *root);
}
