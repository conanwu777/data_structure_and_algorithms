#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	getString(char *tmp, int pos, char *str)
{
	if (!str[0])
		printf("%s\n", tmp);
	else
		for (unsigned int i = 0; i < strlen(str); i++)
		{
			char *rem = strdup(str);
			tmp[pos] = rem[i];
			memmove(&rem[i], &rem[i + 1], strlen(str) - i);
			getString(tmp, pos + 1, rem);
		}
}

void	printPermutations(char *str)
{
	char tmp[strlen(str) + 1];
	tmp[strlen(str)] = 0;
	if (!str)
		return ;
	getString(tmp, 0, str);
}
