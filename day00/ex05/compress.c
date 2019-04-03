#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "header.h"

size_t hash(char *input)
{
	if (!input)
		return (0);
	int m = 0;
	while (input[m] && m < 8)
		m++;
	size_t r = (size_t)input[0];
	for (int i = 1; i < m; i++)
	{
		r <<= 7;
		r += (size_t)input[i];
	}
	return (r);
}

struct s_dict *dictInit(int capacity)
{
	struct s_dict *dict;

	dict = (struct s_dict*)malloc(sizeof(struct s_dict));
	dict->capacity = capacity;
	dict->items = (struct s_item**)malloc(sizeof(struct s_item*) * capacity);
	bzero(dict->items, sizeof(struct s_item*) * capacity);
	return (dict);
}

int	dictInsert(struct s_dict *dict, char *key, int value)
{
	size_t k = hash(key) % (size_t)dict->capacity;
	struct s_item *tmp = (struct s_item*)malloc(sizeof(struct s_item));
	tmp->key = key;
	tmp->value = value;
	tmp->next = NULL;
	if (!dict->items[k])
		dict->items[k] = tmp;
	else
	{
		struct s_item *t = dict->items[k];
		while (t && t->next)
			t = t->next;
		t->next = tmp;
	}
	return (0);
}

int	dictSearch(struct s_dict *dict, char *key)
{
	size_t k = hash(key) % (size_t)dict->capacity;
	if (!(dict->items[k]))
		return (-1);
	struct s_item *t = dict->items[k];
	while (t)
	{
		if (!strcmp(t->key, key))
			return (t->value);
		t = t->next;
	}
	return (-1);
}

char *add_header(char *book, struct s_dict *dict, int n, int N)
{
	char buf[2048];

	int p = 0;
	buf[p] = '<';
	p++;
	for (int c = 0; c < 256; c++)
	{
		int i;
		for (i = 0; i < dict->capacity; i++)
		{
			struct s_item *t = dict->items[i];
			while (t)
			{
				if (t->value == c)
				{
					strcpy(&buf[p], t->key);
					p += strlen(t->key);
					buf[p] = ',';
					p++;
					break ;
				}
				t = t->next;
			}
			if (t)
				break ;
		}
		if (i == dict->capacity)
			break ;
	}
	buf[p] = '>';
	buf[p + 1] = '\n';
	buf[p + 2] = '\0';
	int hl = strlen(buf);
	if (hl >= N - n)
	{
		printf("This is not compressing, it's expansion! Dummy\n");
		exit(1);
	}
	memcpy(&book[hl], &book[0], n);
	memcpy(book, buf, hl);
	return (book);
}

char *compress(char *book, struct s_dict *dict)
{
	char c;
	char buf[14];
	int N = strlen(book);
	int n = N;

	for (int l = 13; l >= 3; l--)
	{
		int p = 0;
		int i = 0;
		char end = 0;
		while (i + l <= n)
		{
			strncpy(buf, &book[i], l);
			buf[l] = 0;
			if ((c = (unsigned char)dictSearch(dict, buf)) != -1)
			{
				book[p] = '@';
				book[p + 1] = c + 1;
				book[p + 2] = 0;
				i += l - 1;
				end = 1;
				p++;
			}
			else
			{
				book[p] = book[i];
				end = 0;
			}
			p++;
			i++;
		}
		if (!end)
			for (int i = n - l + 1; i < n; i++)
			{
				book[p] = book[i];
				p++;
			}
		bzero(&book[p], n - p);
		n = p;
	}
	book = add_header(book, dict, n, N);
	return (book);
}
