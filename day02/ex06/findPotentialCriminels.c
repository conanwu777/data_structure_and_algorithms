#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include "header.h"

typedef struct s_criminal t_criminal;
typedef struct s_info t_info;

int g_size;

int power(int n, int p)
{
	int ret = 1;

	while (p)
	{
		ret *= n;
		p--;
	}
	return (ret);
}

int getDescription(t_info *info)
{
	int sum = 0;
	sum += info->gender;
	sum *= 10;
	sum += info->height;
	sum *= 10;
	sum += info->hairColor;
	sum *= 10;
	sum += info->eyeColor;
	sum *= 10;
	sum += info->glasses;
	sum *= 10;
	sum += info->tattoo;
	sum *= 10;
	sum	+= info->piercing;
	return (sum);
}

void sortFeature(t_criminal **criminals, int i)
{
	t_criminal **arr[10];
	int count[10];
	int j;

	bzero(count, sizeof(int) * 10);
	if (i < 0 || i > 6)
		return ;
	for (int j = 0; j < 10; j++)
		arr[j] = malloc(sizeof(t_criminal*));
	for (j = 0; criminals[j]; j++)
	{
		int t = (criminals[j]->description / power(10, i)) % 10;
		arr[t] = realloc(arr[t], sizeof(t_criminal*) * (count[t] + 1));
		arr[t][count[t]] = criminals[j];
		count[t]++;
	}
	g_size = j;
	int pos = 0;
	for (int j = 0; j < 10; j++)
		for (int k = 0; k < count[j]; k++)
		{
			criminals[pos] = arr[j][k];
			pos++;
		}
	for (int j = 0; j < 10; j++)
		free(arr[j]);
}

void sortCriminals(t_criminal **criminals)
{
	for (int i = 0; i < 7; i++)
		sortFeature(criminals, i);
}

int find_recur(t_criminal **criminals, int size, int n)
{
	if (size < 1)
		return (-1);
	if (size == 1)
		return (criminals[0]->description == n ? 0 : -1);
	int m = size / 2;
	if (criminals[m]->description == n)
		return (m);
	if (criminals[m]->description > n)
		return (find_recur(criminals, m, n));
	return (m + find_recur(&criminals[m], size - m, n));
}

t_criminal **findPotentialCriminals(t_criminal **criminals, t_info *info)
{
	int n = getDescription(info);
	int p = find_recur(criminals, g_size, n);
	if (p == -1)
		return NULL;
	int l = p;
	while (l >= 0 && criminals[l]->description == n)
		l--;
	l++;
	int r = p;
	while (criminals[r] && criminals[r]->description == n)
		r++;
	r--;
	t_criminal **ret = malloc(sizeof(t_criminal*) * (r - l + 2));
	int i = 0;
	while (l <= r)
	{
		ret[i] = criminals[l];
		i++;
		l++;
	}
	ret[i] = NULL;
	return (ret);
}
