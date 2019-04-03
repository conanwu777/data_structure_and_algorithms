#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "header.h"

typedef struct s_stack t_stack;
typedef struct s_item t_item;

t_stack *stackInit(void)
{
	t_stack *stack;
	if (!(stack = (t_stack*)malloc(sizeof(t_stack))))
		return NULL;
	bzero(stack, sizeof(t_stack));
	return (stack);
}

void *pop(t_stack *stack)
{
	void *t;

	if (!stack || !stack->item)
		return (NULL);
	t = (void*)stack->item;
	stack->item = stack->item->next;
	return (t);
}

void push(struct s_stack *stack, char *word)
{
	t_item *t;
	if (!(t = (t_item*)malloc(sizeof(t_item))))
		return ;
	t->word = word;
	t->next = stack->item;
	stack->item = t;
}
//OTHER

void printReverseV2(struct s_node *lst)
{
	struct s_stack *stack = stackInit();
	char st = 1;

	while (lst)
	{
		push(stack, lst->word);
		lst = lst->next;
	}
	while (stack->item)
	{
		if (!st)
			printf(" ");
		st = 0;
		printf("%s", stack->item->word);
		pop(stack);
	}
	printf("\n");
}
