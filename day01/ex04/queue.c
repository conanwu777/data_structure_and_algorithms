#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "header.h"

struct s_queue *queueInit(void)
{
	struct s_queue *queue = (struct s_queue*)malloc(sizeof(struct s_queue));
	bzero(queue, sizeof(struct s_queue));
	return (queue);
}

char *dequeue(struct s_queue *queue)
{
	char *ret;

	struct s_node *t;
	if (!queue || !queue->first)
		return NULL;
	ret = queue->first->message;
	t = queue->first;
	queue->first = queue->first->next;
	free(t);
	return (ret);
}

void enqueue(struct s_queue *queue, char *message)
{
	if (!queue)
		return ;
	struct s_node *t = (struct s_node*)malloc(sizeof(struct s_node *));
	bzero(t, sizeof(struct s_node));
	t->message = message;
	if (!queue->last)
	{
		queue->first = t;
		queue->last = t;
	}
	else
	{
		queue->last->next = t;
		queue->last = t;
	}
}

char *peek(struct s_queue *queue)
{
	if (!queue || !queue->first)
		return NULL;
	return (queue->first->message);
}

int isEmpty(struct s_queue *queue)
{
	if (!queue || !queue->first)
		return (1);
	return (0);
}
