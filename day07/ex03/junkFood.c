#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include "header.h"

typedef struct s_sellers t_sellers;
typedef struct s_graph t_graph;
typedef struct s_node t_node;
typedef struct s_queueItem t_item;
typedef struct s_queue t_queue;

void findSeller(t_sellers *sellers, t_node *me, t_queue *queue, t_graph *graph)
{
	if (!queue->first)
		return ;
	t_queue *nextLevel = queueInit();
	int i = 0;
	while (queue->first)
	{
		if (queue->first->place->hasCerealBar)
			sellers->placeNames[i++] = queue->first->place->name;
		for (int i = 0; queue->first->place->connectedPlaces[i]; i++)
			if (queue->first->place->connectedPlaces[i]->visited == 0)
			{
				queue->first->place->connectedPlaces[i]->visited = 1;
				enqueue(nextLevel, queue->first->place->connectedPlaces[i]);
			}
		dequeue(queue);
	}
	if (sellers->placeNames[0])
		return ;
	sellers->distance++;
	t_node *tmp;
	while (nextLevel->first)
	{
		tmp = dequeue(nextLevel);
		enqueue(queue, tmp);
	}
	free(nextLevel);
	findSeller(sellers, me, queue, graph);
}

t_sellers *closestSellers(t_graph *graph, char *youAreHere)
{
	t_node *me = NULL;
	int i;
	for (i = 0; graph->places[i]; i++)
		if (!strcmp(graph->places[i]->name, youAreHere))
			me = graph->places[i];
	if (!me)
		return NULL;
	me->visited = 1;
	t_sellers *sellers = calloc(1, sizeof(t_sellers));
	sellers->distance = 0;
	sellers->placeNames = calloc(i + 1, sizeof(char*));
	t_queue *queue = queueInit();
	enqueue(queue, me);
	findSeller(sellers, me, queue, graph);
	for (i = 0; graph->places[i]; i++)
		graph->places[i]->visited = 0;
	while (queue->first)
		dequeue(queue);
	free(queue);
	return sellers;
}
