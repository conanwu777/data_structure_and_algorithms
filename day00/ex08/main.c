#include <stdio.h> //printf, scanf, ...
#include <string.h> //memcpy, strlen, ...
#include <unistd.h> //fork, write, sleep...
#include <stdlib.h> //malloc, free, exit...

#include "header.h"

int main(int ac, char **av)
{
	/*-------------------
	launch your test here
	--------------------*/

	printf("%s replace %d with %c results in %s\n", "hello", 1, 'a', replace("hello", 1, 'a'));
	printf("%s replace %d with %c results in %s\n", "hello", 100, 'a', replace("hello", 100, 'a'));
	printf("%s delete %d results in %s\n", "hello", 1, delete("hello", 1));
	printf("%s add %d with %c results in %s\n", "hello", 1, 'a', add("hello", 1, 'a'));
	printf("%s add %d with %c results in %s\n", "hello", 0, 'a', add("hello", 0, 'a'));
	printf("\n");
	if (ac >= 3) {
		printf("most closest word: %s\n", whatWasThat(av[1], av + 2));
	} else {
		printf("usage: ./whatWasThat word   dict1 dict2 dict3 ...\n");
	}
	return (0);
}

// Function used for the test
// Don't go further :)
