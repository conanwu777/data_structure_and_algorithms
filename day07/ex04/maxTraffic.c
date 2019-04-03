#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "header.h"

typedef struct s_graph t_graph;
typedef struct s_node t_node;
typedef struct s_queueItem t_item;
typedef struct s_queue t_queue;

void expanding(t_queue *queue, t_node *me)
{
	while (queue->first)
	{
		t_queue *nxLevel = queueInit();
		while (queue->first)
		{
			for (int j = 0; queue->first->item->connectedPlaces[j]; j++)
				if (queue->first->item->connectedPlaces[j] == me)
					continue ;
				else if (queue->first->item->connectedPlaces[j]->visited == 0)
				{
					enqueue(nxLevel, queue->first->item->connectedPlaces[j]);
					queue->first->item->connectedPlaces[j]->visited = queue->first->item->visited;
				}
				else if (queue->first->item->connectedPlaces[j]->visited >= 0)
				{
					t_item *tmp = nxLevel->first;
					while (tmp)
					{
						if (tmp->item == queue->first->item->connectedPlaces[j])
							tmp->item->visited += queue->first->item->visited;
						tmp = tmp->next;
					}
				}
			dequeue(queue);
		}
		t_queue *tmp = queue;
		queue = nxLevel;
		free(tmp);
	}
}

float maxTraffic(struct s_graph *parisPlaces, char *eventHere)
{
	t_node *me = NULL;
	for (int i = 0; parisPlaces->places[i]; i++)
		if (!strcmp(parisPlaces->places[i]->name, eventHere))
			me = parisPlaces->places[i];
	if (!me)
		return -1;
	int k;
	t_queue *queue = queueInit();
	for (k = 0; me->connectedPlaces[k]; k++)
	{
		if (me->connectedPlaces[k] == me)
			continue ;
		enqueue(queue, me->connectedPlaces[k]);
		me->connectedPlaces[k]->visited += 1 << 8 * k;
	}
	if (k >= 8)
		return (printf("Error: Current implementation only handle event node with <= 8 neighbours\n"));
	expanding(queue, me);
	float res[k];
	for (int i = 0; i < k; i++)
		res[i] = 0;
	for (int j = 0; parisPlaces->places[j]; j++)
	{
		if (parisPlaces->places[j] == me)
			continue ;
		int totalPaths = 0;
		int pathNum[k];
		for (int i = 0; i < k; i++)
		{
			pathNum[i] = (parisPlaces->places[j]->visited >> 8 * i) & 255;
			totalPaths += pathNum[i];
		}
		for (int i = 0; i < k; i++)
			res[i] += (float)parisPlaces->places[j]->population
		* (float)pathNum[i] / (float)totalPaths;
		parisPlaces->places[j]->visited = 0;
	}
	float max = res[0];
	for (int i = 0; i < k; i++)
		if (res[i] > max)
			max = res[i];
	return (max);
}
