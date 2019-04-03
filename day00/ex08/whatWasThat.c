#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "header.h"

char    *delete(char *word, int pos)
{
	int i;

	if (pos < 0 || pos >= (int)strlen(word))
		return NULL;
	char *new = malloc(strlen(word));
	for (i = 0; i < pos; i++)
		new[i] = word[i];
	i++;
	while (i < (int)strlen(word))
	{
		new[i - 1] = word[i];
		i++;
	}
	new[i - 1] = 0;
	return (new);
}

char    *replace(char *word, int pos, char c)
{
	if (pos < 0 || pos >= (int)strlen(word))
		return NULL;
	char *new = strdup(word);
	new[pos] = c;
	return (new);
}

char    *add(char *word, int pos, char c)
{
	int i;

	if (pos < 0 || pos > (int)strlen(word))
		return NULL;
	char *new = malloc(strlen(word) + 2);
	new = strcpy(new, word);
	new[pos] = c;
	for (i = pos; word[i]; i++)
		new[i + 1] = word[i];
	new[i + 1] = 0;
	return (new);
}

int min3(int a, int b, int c)
{
	if (a < b)
		return (a < c ? a : c);
	else
		return (b < c ? b : c);
}

int		dist(char *s1, char *s2)
{
	int h = strlen(s2) + 1;
	int w = strlen(s1) + 1;
	int arr[h][w];
	int min;

	for (int i = 0; i < w; i++)
		arr[0][i] = i;
	for (int j = 1; j < h; j++)
	{
		arr[j][0] = j;
		for (int i = 1; i < w; i++)
		{
			min = min3(arr[j][i - 1], arr[j - 1][i - 1], arr[j - 1][i]);
			if (s1[i - 1] == s2[j - 1])
				arr[j][i] = min;
			else
				arr[j][i] = min + 1;
		}
	}
	return (arr[h - 1][w - 1]);
}

char	*whatWasThat(char *word, char **dict)
{
	int i = 0;
	int min = DEPTH + 1;
	int t;
	char *ret = NULL;

	while (dict[i])
	{
		t = dist(word, dict[i]);
		if (t < min)
		{
			min = t;
			ret = dict[i];
		}
		i++;
	}
	return ret;
}
