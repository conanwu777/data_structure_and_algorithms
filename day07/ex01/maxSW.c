#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

#include "header.h"

typedef struct s_deque t_deque;
typedef struct s_dequeNode t_node;
typedef struct s_max t_max;

struct s_deque *dequeInit(void)
{
	t_deque *deque = calloc(1, sizeof(t_deque));
	return deque;
}

void pushFront(struct s_deque *deque, int value)
{
	t_node *tmp = calloc(1, sizeof(t_node));
	tmp->value = value;
	if (deque->first)
	{
		deque->first->prev = tmp;
		tmp->next = deque->first;
	}
	else
		deque->last = tmp;
	deque->first = tmp;
}

void pushBack(struct s_deque *deque, int value)
{
	t_node *tmp = calloc(1, sizeof(t_node));
	tmp->value = value;
	if (deque->last)
	{
		deque->last->next = tmp;
		tmp->prev = deque->last;
	}
	else
		deque->first = tmp;
	deque->last = tmp;
}

int popFront(struct s_deque *deque)
{
	if (!deque->first)
		return INT_MIN;
	t_node *tmp = deque->first;
	int t = tmp->value;
	deque->first = deque->first->next;
	if (deque->first)
		deque->first->prev = NULL;
	return t;
}

int popBack(struct s_deque *deque)
{
	if (!deque->last)
		return INT_MIN;
	t_node *tmp = deque->last;
	int t = tmp->value;
	deque->last = deque->last->prev;
	if (deque->last)
		deque->last->next = NULL;
	return t;
}

struct s_max *maxSlidingWindow(int *arr, int n, int k)
{
	if (k < 1)
		return NULL;
	t_max *max = calloc(1, sizeof(t_max));
	max->length = n - k + 1;
	max->max = calloc(n - k + 1, sizeof(int));
	t_deque *deque = dequeInit();
	for (int i = 0; i < k; i++)
	{
		while (deque->last && arr[deque->last->value] <= arr[i])
			popBack(deque);
		pushBack(deque, i);
	}
	for (int i = k; i <= n; i++)
	{
		if (deque->first)
			max->max[i - k] = arr[deque->first->value];
		if (deque->first && deque->first->value <= i - k)
			popFront(deque);
		while (deque->last && arr[deque->last->value] <= arr[i])
			popBack(deque);
		pushBack(deque, i);
	}
	return max;
}
