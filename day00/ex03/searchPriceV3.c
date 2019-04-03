#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "header.h"

size_t hash(char *input)
{
	size_t ret = strlen(input);
	for (unsigned int i = 0; i < strlen(input) && i < 10; i++)
	{
		ret <<= 4;
		ret += (unsigned char)input[i];
	}
	return (ret);
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

int	dictInsert(struct s_dict *dict, char *key, struct s_art *value)
{
	int k = (unsigned int)hash(key) % dict->capacity;
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

struct s_art *dictSearch(struct s_dict *dict, char *key)
{
	int k = (unsigned int)hash(key) % dict->capacity;

	if (!(dict->items[k]))
		return (NULL);
	struct s_item *t = dict->items[k];
	while (t)
	{
		if (!strcmp(t->value->name, key))
			return (t->value);
		t = t->next;
	}
	return (NULL);
}

int searchPrice(struct s_dict *dict, char *name)
{
	struct s_art *tmp;
	if ((tmp = dictSearch(dict, name)))
		return (tmp->price);
	return (-1);
}
