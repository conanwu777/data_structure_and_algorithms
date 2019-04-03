#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "header.h"

char *NthLastCity(struct s_city *city, int n)
{
	struct s_city *t;

	t = city;
	if (n < 0)
		return NULL;
	while (n-- > 0)
	{
		if (!t->next)
			return NULL;
		t = t->next;
	}
	t = t->next;
	while (t)
	{
		t = t->next;
		city = city->next;
	}
	return (city->name);
}
