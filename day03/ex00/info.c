#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include "header.h"

typedef struct s_node t_node;
typedef struct s_info t_info;

t_info combine(t_info left, t_info right)
{
	t_info res;

	if (left.elements == 0)
	{
		right.isBalanced = (right.elements == 1 ? 1 : 0);
		return right;
	}
	if (right.elements == 0)
	{
		left.isBalanced = (left.elements == 1 ? 1 : 0);
		return left;
	}
	res.min = (left.min <= right.min ? left.min : right.min);
	res.max = (left.max >= right.max ? left.max : right.max);
	res.elements = left.elements + right.elements;
	res.height = (left.height >= right.height ? left.height : right.height);
	res.isBST = (left.max < right.min ? 1 : 0);
	res.isBalanced = (abs(left.elements - right.elements) <= 1);
	return res;
}

struct s_info   getInfo(struct s_node *root)
{
	t_info info;

	if (!root)
	{
		info.elements = 0;
		return info;
	}
	if (!root->left && !root->right)
	{
		info.min = root->value;
		info.max = root->value;
		info.elements = 1;
		info.height = 0;
		info.isBST = 1;
		info.isBalanced = 1;
		return info;
	}
	t_info rightInfo = getInfo(root->right);
	info = combine(getInfo(root->left), rightInfo);
	info.min = (root->value < info.min ? root->value : info.min);
	info.max = (root->value > info.max ? root->value : info.max);
	info.elements += 1;
	info.height += 1;
	if (info.isBST && (!root->left || root->left->value <= root->value)
		&& (!root->right || root->value < rightInfo.min))
		info.isBST = 1;
	else
		info.isBST = 0;
	return info;
}