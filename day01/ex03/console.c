#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "header.h"

struct s_stack *stackInit(void)
{
	struct s_stack *stack = (struct s_stack*)malloc(sizeof(struct s_stack));
	bzero(stack, sizeof(struct s_stack));
	return (stack);
}

int pop(struct s_stack *stack)
{
	struct s_item *t;
	if (!stack || !stack->item)
		return (-1);
	int idx = stack->item->idx;
	t = stack->item;
	if (!stack->item->next)
		stack->item = NULL;
	else
		stack->item = stack->item->next;
	free(t);
	return (idx);
}

void push(struct s_stack *stack, int idx)
{
	struct s_item *t = (struct s_item*)malloc(sizeof(struct s_item));
	t->idx = idx;
	t->next = stack->item;
	stack->item = t;
}

char *console(void)
{
	char *buf = (char*)malloc(281);
	struct s_stack *stack = stackInit();

	push(stack, 0);
	printf("👽  ?> ");
	while (fgets(&buf[stack->item->idx], 280 - stack->item->idx, stdin))
	{
		buf[strlen(buf) - 1] = '\0';
		if (strlen(buf) > 0)
		{
			if (!strcmp(&buf[stack->item->idx], "UNDO"))
			{
				int i = pop(stack);
				if (i == 0)
					push(stack, 0);
				bzero(&buf[stack->item->idx], 280 - stack->item->idx);
			}
			else if (!strcmp(&buf[stack->item->idx], "SEND"))
			{
				bzero(&buf[stack->item->idx], 280 - stack->item->idx);
				return (buf);
			}
			else
				push(stack, stack->item->idx + strlen(&buf[stack->item->idx]));
			if (buf[0])
				printf("%s\n", buf);
		}
		printf("\n");
		printf("👽  ?> ");
	}
	return (buf);
}
