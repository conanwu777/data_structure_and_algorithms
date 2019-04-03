#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_node t_node;
typedef struct s_dict t_dict;

int minRecur(t_node *begin, t_node *end, int n, t_dict *dict)
{
	if (dictSearch(dict, begin) != -1)
		return dictSearch(dict, begin);
	if (begin == end || n == 0)
		return 0;
	int min = begin->next ? minRecur(begin->next, end, n - 1, dict) : 0;
	int tmp;
	if (begin->random &&
		(tmp = minRecur(begin->random, end, n - 1, dict)) < min)
			min = tmp;
	dictInsert(dict, begin, min + 1);
	return min + 1;
}

int	minimumMoves(struct s_node *begin)
{
	int n = 0;
	t_node *end = begin;

	while (end->next && n++ >= 0)
		end = end->next;
	t_dict *dict = dictInit(n);
	return (minRecur(begin, end, n, dict));
}
