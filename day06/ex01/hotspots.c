#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "header.h"

int selectHotspots(struct s_hotspot **hotspots)
{
	int n = 0;
	for (int i = 0; hotspots[i]; i++)
	{
		hotspots[i]->pos += hotspots[i]->radius;
		hotspots[i]->radius *= 2;
		n++;
	}
	int r = 1;
	int pos = hotspots[0]->pos;
	for (int i = 1; i < n; i++)
		if (hotspots[i]->pos - hotspots[i]->radius >= pos)
		{
			pos = hotspots[i]->pos;
			r++;
		}
	return r;
}
