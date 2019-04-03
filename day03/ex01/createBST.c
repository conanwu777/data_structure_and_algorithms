#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include "header.h"

typedef struct s_node t_node;

struct s_node *createBST(int *arr, int n)
{
	if (n <= 0)
		return NULL;
	t_node *t = malloc(sizeof(t_node));
	bzero(t, sizeof(t_node));
	t->value = arr[n / 2];
	if (n == 1)
		return t;
	if (n == 2)
	{
		t->value = arr[0];
		t->right = createBST(&arr[1], n / 2);
		t->left = NULL;
		return t;
	}
	t->left = createBST(arr, n / 2);
	t->right = createBST(&arr[n / 2 + 1], n - n / 2 - 1);
	return t;
}
