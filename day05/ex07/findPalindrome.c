#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *findPalindrome_recur(char *sequence, int nDelete, int pos)
{
	int n = strlen(sequence);
	while (pos < n / 2 + 1 && sequence[pos] == sequence[n - 1 - pos])
		pos++;
	if (pos == n / 2 + 1)
		return sequence;
	if (nDelete == 0)
		return NULL;
	char *res;
	char *tmp = strdup(sequence);
	memmove(&tmp[pos], &tmp[pos + 1], n - pos);
	if ((res = findPalindrome(tmp, nDelete - 1)))
		return (res);
	strcpy(tmp, sequence);
	memmove(&tmp[n - 1 - pos], &tmp[n - pos], pos + 1);
	if ((res = findPalindrome(tmp, nDelete - 1)))
		return (res);
	free(tmp);
	return 0;
}

char *findPalindrome(char *sequence, int nDelete)
{
	return (sequence ? findPalindrome_recur(sequence, nDelete, 0) : NULL);
}
