#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "header.h"

struct s_string *stringInit(void)
{
	struct s_string *str;

	str = (struct s_string*)malloc(sizeof(struct s_string));
	str->content = (char*)malloc(33);
	bzero(str->content, 32);
	str->length = 0;
	str->capacity = 32;
	return (str);
}

int	stringAppend(struct s_string *s, char *add) //return 0 = FAIL, 1 = SUCCESS
{
	int len = strlen(add);
	if (s->length + len > s->capacity)
	{
		int i = s->capacity;
		while (i < s->length + len)
			i *= 2;
		char *new;
		if(!(new = (char*)malloc(i + 1)))
			return (0);
		bzero(new, i + 1);
		s->capacity = i;
		memcpy(new, s->content, s->length);
		memcpy(&new[s->length], add, strlen(add));
		free(s->content);
		s->content = new;
		s->length += len;
	}
	else
	{
		memcpy(&(s->content[s->length]), add, strlen(add));
		s->length += len;
	}
	return (1);
}
// OTHER
char	**split(char *str, char *delimiter){
	char **tab;
	int count;
	int a;
	int pos;
	int len_delimiter;
	int len_substring;

	len_delimiter = strlen(delimiter);
	len_substring = 0;
	count = 0;
	for (int i = 0; str[i]; i++){
		if (strncmp(str + i, delimiter, len_delimiter) == 0) {
			if (len_substring > 0){
				len_substring = 0;
				count += 1;
			}
			i += len_delimiter - 1;
		} else {
			len_substring += 1;
		}
	}
	if (len_substring > 0){
		count += 1;
	}
	if (NULL == (tab = malloc(sizeof(char *) * (count + 1))))
		return (NULL);
	tab[(a = 0)] = NULL;
	len_substring = 0;
	pos = 0;
	for (int i = 0; str[i]; i++){
		if (strncmp(str + i, delimiter, len_delimiter) == 0) {
			if (len_substring > 0){
				tab[(a++)] = strndup(str + pos, len_substring);
				len_substring = 0;
			}
			i += len_delimiter - 1;
			pos = i + 1;
		} else {
			len_substring += 1;
		}
	}
	if (len_substring > 0){
		tab[(a++)] = strndup(str + pos, len_substring);
	}
	tab[a] = NULL;
	return (tab);
}

void readWords(char *src, int len, char ***pWords, int *pLenWords)
{
	src[len] = '\0';
	(*pWords) = split(src, ",");
	*pLenWords = 0;
	for ((*pLenWords) = 0; (*pWords)[(*pLenWords)]; (*pLenWords)++)
		;
}

char *decompress(char *cBook)
{
	char **words;
	int lenWords;
	struct s_string *new;
	char *output;

	int st = 0;
	int l = 0;
	while (cBook[st] && cBook[st] != '<')
		st++;
	st++;
	for (l = 0; cBook[l] && cBook[l] != '>'; l++)
		;
	readWords(&cBook[st], l, &words, &lenWords);
	st += l + 1;
	new = stringInit();
	while (cBook[st])
	{
		int i = 0;
		while (cBook[st + i] && cBook[st + i] != '@')
			i++;
		if (!cBook[st + i])
		{
			stringAppend(new, &cBook[st]);
			break ;
		}
		cBook[st + i] = '\0';
		stringAppend(new, &cBook[st]);
		st += i + 1;
		stringAppend(new, words[cBook[st] - 1]);
		st++;
	}
	for (int i = 0; i < lenWords; i++)
		free(words[i]);
	free(words);
	output = new->content;
	free(new);
	return (output);
}
