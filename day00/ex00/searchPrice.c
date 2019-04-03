#include <string.h>
#include "header.h"

int  searchPrice(struct s_art **arts, char *name)
{
	while (*arts && (*arts)->name)
	{
		if (!strcmp(name, (*arts)->name))
			return ((*arts)->price);
		arts++;
	}
	return (-1);
}
