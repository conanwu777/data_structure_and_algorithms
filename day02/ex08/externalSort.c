#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include "header.h"

typedef struct s_block t_block;

int getSize(char *scoreFile)
{
	char buf[256];
	FILE *f = fopen(scoreFile, "r");
	int size = 0;
	while (fgets(buf, sizeof(buf), f))
		size++;
	fclose(f);
	return size;
}

char *filename(int lv, int n)
{
	char *buf = malloc(256);

	sprintf(buf, "lv%dfile%.3d", lv, n);
	return buf;
}

int createFiles(char *scoreFile, int size, int ram)
{
	t_block *block;
	int st = 0;
	int end = ram / sizeof(int);
	int count = 0;

	while (st < size - 1)
	{
		block = fileGetBlock(scoreFile, st, end);
		for (int i = 1; i <= block->n; i++)
		{
			int tmp = block->scores[i];
			for (int j = 0; j < i; j++)
			{
				if (tmp < block->scores[j])
				{
					memcpy(&block->scores[j + 1], &block->scores[j], sizeof(int) * (i - j));
					block->scores[j] = tmp;
					break ;
				}
			}
		}
		filePutBlock(filename(0, count), block);
		free(block);
		st = end;
		end += ram / sizeof(int);
		if (end > size)
			end = size - 1;
		count++;
	}
	return count;
}

void mergeFiles(char *file1, char *file2, char *tar)
{
	FILE *tmp = fopen(tar, "w+");
	FILE *f1 = fopen(file1, "r");
	FILE *f2 = fopen(file2, "r");
	int sz1, sz2;
	fscanf(f1, "%d", &sz1);
	fscanf(f2, "%d", &sz2);
	fprintf(tmp, "%d\n", sz1 + sz2);
	int t1, t2;
	fscanf(f1, "%d", &t1);
	fscanf(f2, "%d", &t2);
	while (t1 >= 0 || t2 >= 0)
	{
		if (t2 == -1 || (t1 >= 0 && t1 < t2))
		{
			fprintf(tmp, "%d\n", t1);
			if (fscanf(f1, "%d", &t1) == EOF)
				t1 = -1;
		}
		else
		{
			fprintf(tmp, "%d\n", t2);
			if (fscanf(f2, "%d", &t2) == EOF)
				t2 = -1;
		}
	}
	fclose(f1);
	fclose(f2);
	fclose(tmp);
}

void copyOutput(char *f1, char *f2)
{
	FILE *in = fopen(f1, "r");
	FILE *out = fopen(f2, "w");

	int db;
	fscanf(in, "%d", &db);
	while (fscanf(in, "%d", &db) != EOF)
		fprintf(out, "%d\n", db);
	fclose(in);
	fclose(out);
}

void externalSort(char *scoreFile, char *sortedFile, int ram)
{
	int size = getSize(scoreFile);
	(void)size;
	(void)ram;
	int count = createFiles(scoreFile, size, ram);
	printf("%d\n", count);
	int lv = 1;
	while (count >= 1)
	{
		int i;
		for (i = 0; 2 * i <= count; i++)
		{
			if (!(fopen(filename(lv - 1, 2 * i + 1), "r")))
			{
				rename(filename(lv - 1, 2 * i), filename(lv, i));
				continue;
			}
			mergeFiles(filename(lv - 1, 2 * i), filename(lv - 1, 2 * i + 1), filename(lv, i));
			remove(filename(lv - 1, 2 * i));
			remove(filename(lv - 1, 2 * i + 1));
		}
		count = i - 1;
		lv++;
	}
	copyOutput(filename(lv - 1, 0), sortedFile);
	remove(filename(lv - 1, 0));
}
