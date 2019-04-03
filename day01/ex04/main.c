#include <stdio.h> //printf, scanf, ...
#include <string.h> //memcpy, strlen, ...
#include <unistd.h> //fork, write, sleep...
#include <stdlib.h> //malloc, free, exit...

#include "header.h"

int main(void)
{

	/*-------------------
	launch your test here
	--------------------*/

	char *str = malloc(10);
    strcpy(str, "wowow");

    printf("Initialize the queue\n");
    struct s_queue* qu = queueInit();
    printf("empty : %d\n",isEmpty(qu));
    printf("This is the first little message\n");
    enqueue(qu, "This is the first little message");
    printf("This is the second little message\n");
    enqueue(qu, "This is the second little message");
    printf("empty : %d\n",isEmpty(qu));
    printf("peek : %s\n", peek(qu));
    printf("dequeue : %s\n", dequeue(qu));
    printf("dequeue : %s\n", dequeue(qu));
    printf("dequeue : %s\n", dequeue(qu));
    printf("dequeue : %s\n", dequeue(qu));
    printf("peek : %s\n", peek(qu));
    free(str);
	return (0);
}

// Function used for the test
// Don't go further :)

