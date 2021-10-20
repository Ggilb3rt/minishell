//
// Created by antoine on 15/10/2021.
//

#include "minishell.h"

static int check_quote(char c)
{
	if (c == '\'')
		return (1);
	else if (c == '\"')
		return (2);
	else
		return (0);
}

static int  go_next_quote(char *str, int i, int open)
{
	char c;

	if (open == 1)
		c = '\'';
	else if (open == 2)
		c = '\"';
	while (str[i] != c)
	{
		if (str[i] == '\0')
			return (0);
		i++;
	}
	return (i);
}

static int 	meet_quote(char *str, int i, int *open)
{
	int jmp;

	i++;
	jmp = go_next_quote(str, i, *open);
	if (jmp > 0)
	{
		i = jmp;
		*open = 0;
	}
	else
		printf("error next quote\n");
	return (i);
}

int 	word_count(char *str)
{
	int	words;
	int	trig;
	int i;
	int open;

	open = 0;
	i = 0;
	words = 0;
	trig = 0;
	while (str[i])
	{
		open = check_quote(str[i]);
		if (open)
		{
			i = meet_quote(str, i, &open);
			words++;
			if (ms_is_alpha(&str[i + 1]))
				trig = 0;
		}
		else if ((str[i] != ' ' && !open) && trig == 0)
		{
			trig = 1;
			words++;
		}
		else if (str[i] == ' ')
			trig = 0;
		i++;
	}
	return (words);
}

char *split_words(char *str, int strt, int fnsh)
{
	char *word;
	int i;

	i = 0;
	word = malloc(sizeof(char) * (fnsh - strt + 1));
	while (strt < fnsh)
	{
		word[i] = str[strt];
		i++;
		strt++;
	}
	word[i] = '\0';
	return (word);
}