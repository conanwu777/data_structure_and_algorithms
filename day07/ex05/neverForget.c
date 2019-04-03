#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "header.h"

char *al = "abcdefghijklmnopqrstuvwxyz";

int findSub(char **tab, char **blank, t_trie *trie, char *a)
{
	if (!a || !*a)
		return 1;
	for (char c = 'a'; c <= 'z'; c++)
	{
		int i;
		for (i = 0; tab[i]; i++)
		{
			for (int j = 0; tab[i][j]; j++)
				if (tab[i][j] == *a)
					blank[i][j] = c;
			if (!(*understand(blank[i], trie)))
				break ;
		}
		if (!tab[i])
			if (findSub(tab, blank, trie, a + 1))
				return 1;
	}
	for (int i = 0; tab[i]; i++)
		for (int j = 0; tab[i][j]; j++)
			if (tab[i][j] == *a)
				blank[i][j] = '?';
	return 0;
}

int *countFrequency(char *words)
{
	int *f = calloc(26, sizeof(int));
	for (int i = 0; words[i]; i++)
		if (words[i] != ' ')
			f[words[i] - 'a']++;
	return f;
}

char *sortFrequency(int *f)
{
	char *a = strdup(al);
	for (int i = 0; i < 25; i++)
		for (int j = i + 1; j < 26; j++)
			if (f[i] < f[j])
			{
				int t = f[i];
				char c = a[i];
				f[i] = f[j];
				a[i] = a[j];
				f[j] = t;
				a[j] = c;
			}
	return a;
}

char *neverForget(char *words, char **dictionary)
{
	for (int i = 0; words[i]; i++)
		if (words[i] != ' ' && (words[i] < 'a' || words[i] > 'z'))
			return NULL;
	char *ret = strdup(words);
	int *f = countFrequency(words);
	t_trie *trie = createTrie(dictionary);
	char **tab = calloc(strlen(words), sizeof(char*));
	char **blank = calloc(strlen(words), sizeof(char*));
	char *token = strtok(ret, " \n");
	int i = 0;
	while (token != NULL)
	{
		tab[i] = token;
		blank[i] = calloc(strlen(token) + 1, sizeof(char));;
		memset(blank[i], '?', strlen(token));
		token = strtok(NULL, " \n");
		i++;
	}
	char *a = sortFrequency(f);
	if (!findSub(tab, blank, trie, a))
		return NULL;
	char *tmp;
	for (int i = 0; tab[i]; i++)
	{
		strcpy(tab[i], blank[i]);
		tmp = tab[i] + strlen(tab[i]);
		*tmp = *(words + (int)(tmp - ret));
	}
	return ret;
}
