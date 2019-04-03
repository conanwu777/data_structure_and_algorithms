#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include "header.h"

typedef struct s_graph t_graph;
typedef struct s_node t_node;
typedef struct s_edge t_edge;

void recurPrint(t_graph *tree, t_graph *graph, int k, int n)
{
	if (!tree || !tree->nodes[0] || !tree->nodes[0]->edges[0])
		return ;
	int min = INT_MAX;
	t_node *st = NULL;
	t_edge *ed = NULL;
	for (int i = 0; tree->nodes[i]; i++)
		for (int j = 0; tree->nodes[i]->edges[j]; j++)
			if (tree->nodes[i]->edges[j]->dist < min)
			{
				int k;
				for (k = 0; tree->nodes[k]; k++)
					if (tree->nodes[i]->edges[j]->dest == tree->nodes[k])
						break ;
				if (!tree->nodes[k])
				{
					min = tree->nodes[i]->edges[j]->dist;
					st = tree->nodes[i];
					ed = tree->nodes[i]->edges[j];
				}
			}
	printf("distance: %d : Node %d - Node %d\n", ed->dist, st->id, ed->dest->id);
	tree->nodes[k] = ed->dest;
	k++;
	if (k < n)
		recurPrint(tree, graph, k, n);
}

void printMST(struct s_graph *graph)
{
	int n;
	for (n = 0; graph->nodes[n]; n++)
		;
	t_graph *tree = malloc(sizeof(t_graph));
	tree->nodes = calloc(n + 1, sizeof(t_node*));
	tree->nodes[0] = graph->nodes[0];
	recurPrint(tree, graph, 1, n);
	free(tree->nodes);
	free(tree);
}
