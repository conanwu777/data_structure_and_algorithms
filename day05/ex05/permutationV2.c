#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_dict t_dict;

int		fact(int n)
{
	return (n <= 1 ? 1 : n * fact(n - 1));
}

void	recur(char *tmp, int pos, char *str, t_dict *dict)
{
	if (!str[0] && dictSearch(dict, tmp) == -1 && printf("%s\n", tmp) >= -1)
		dictInsert(dict, tmp, 1);
	else if (str[0])
		for (unsigned int i = 0; i < strlen(str); i++)
		{
			char *rem = strdup(str);
			tmp[pos] = rem[i];
			memmove(&rem[i], &rem[i + 1], strlen(str) - i);
			recur(tmp, pos + 1, rem, dict);
		}
}

void	printUniquePermutations(char *str)
{
	if (!str)
		return ;
	int n = strlen(str);
	char tmp[n + 1];
	tmp[n] = 0;
	t_dict *dict = dictInit(fact(n));
	recur(tmp, 0, str, dict);
}
