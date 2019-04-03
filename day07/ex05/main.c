#include <stdio.h> //printf, scanf, ...
#include <string.h> //memcpy, strlen, ...
#include <unistd.h> //fork, write, sleep...
#include <stdlib.h> //malloc, free, exit...

#include "header.h"
#include "dictionary.c"

int main(int ac, char **av)
{
	char *input;
	char *output;

	if (ac != 2)
		return (-1);
	if (!(input = get_content(av[1])))
		return (-1);
	output = NULL;

	/*-------------------
	launch your test here
	--------------------*/

	if (!(output = neverForget(input, g_dict)))
		return (-1);
	printf("%s\n", output);
	
	return (0);
}

// Function used for the test
// Don't go further :)

void addLetter(t_node **tp, char **dictionary, int i, int j)
{
	t_node *t = *tp;
	int k;
	for (k = 0; t->child[k]; k++)
		if (t->child[k]->c == dictionary[i][j])
		{
			*tp = t->child[k];
			if (!dictionary[i][j + 1])
				t->isWord = 1;
			return ;
		}
	if (!t->child[k])
	{
		t->child = realloc(t->child, sizeof(t_node*) * (k + 2));
		t->child[k] = malloc(sizeof(t_node));
		t->child[k]->c = dictionary[i][j];
		t->child[k]->isWord = (!dictionary[i][j + 1] ? 1 : 0);
		t->child[k]->child = malloc(sizeof(t_node*));
		t->child[k]->child[0] = NULL;
		t->child[k + 1] = NULL;
		*tp = t->child[k];
	}
}

struct s_trie *createTrie(char **dictionary)
{
	t_trie *trie = malloc(sizeof(t_trie));
	trie->node = malloc(sizeof(t_node));
	t_node *root = trie->node;
	root->c = -1;
	root->child = malloc(sizeof(t_node*));
	root->child[0] = NULL;
	for (int i = 0; dictionary[i]; i++)
	{
		t_node *t = root;
		for (int j = 0; dictionary[i][j]; j++)
			addLetter(&t, dictionary, i, j);
	}
	return trie;
}

int caseNormal(char *word, char **buf, t_node *node)
{
	for (int k = 0; node->child[k]; k++)
		if (node->child[k]->c == word[0])
		{
			if (!word[1])
			{
				if (node->child[k]->isWord)
				{
					(*buf)[0] = word[0];
					return 1;
				}
			}
			else if (recur(&word[1], buf, node->child[k]))
			{
				memcpy(*buf + 1, *buf, strlen(*buf));
				(*buf)[0] = word[0];
				return 1;
			}
		}
	return 0;
}

int caseWild(char *word, char **buf, t_node *node)
{
	for (int k = 0; node->child[k]; k++)
		if (!word[1])
		{
			if (node->child[k]->isWord)
			{
				(*buf)[0] = node->child[k]->c;
				return 1;
			}
		}
		else if (recur(&word[1], buf, node->child[k]))
		{
			memcpy(*buf + 1, *buf, strlen(*buf));
			(*buf)[0] = node->child[k]->c;
			return 1;
		}
	return 0;
}

int recur(char *word, char **buf, t_node *node)
{
	if (word[0] != '?')
		return (caseNormal(word, buf, node));
	else
		return (caseWild(word, buf, node));
}

char *understand(char *word, struct s_trie *trie)
{
	char *buf = malloc(100);
	bzero(buf, 100); 
	recur(word, &buf, trie->node);
	return (buf);
}

char *get_content(char *file) {
	FILE *f = fopen(file, "r");
	char buffer[100];
	char *str;
	int count;
	int len;

	len = 0;
	for (count = 0; fscanf(f, "%s", buffer) > 0; count++) {
		len += strlen(buffer);
	}
	fclose(f);
	f = fopen(file, "r");
	if (!(str = (char *)malloc(sizeof(char) * (len + count + 1))))
		return (NULL);
	for (int i = 0; fscanf(f, "%s", buffer) > 0; i++) {
		strcat(str, buffer);
		if (i < count - 1)
			strcat(str, " ");
	}

	return (str);
}
