/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alangloi <alangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 14:15:14 by alangloi          #+#    #+#             */
/*   Updated: 2021/10/19 14:15:48 by alangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	else
		return (0);
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

static int 	word_count(char *str)
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

static char *split_words(char *str, int strt, int fnsh)
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

char **split_quote(char *str)
{
	int		i;
	int 	j;
	char 	**new;
	int 	size;
	int		count;
	int 	count_s;
	int 	count_d;
	int		len;
	int		open;

	open = 0;
	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	size = word_count(str);
	len = ms_strlen(str);
	count = -1;
	count_s = -1;
	count_d = -1;
	new = malloc(sizeof(char *) * size + 1);
	if (!new)
		return (NULL);
	while (i <= len)
	{
		if ((str[i] == '\"' || str[i] == '\'') && open == 0 && count < 0)
		{
			if (str[i] == '\'')
			{
				count_s = i;
				open = 1;
			}
			else if (str[i] == '\"')
			{
				count_d = i;
				open = 2;
			}
		}
		else if (open == 0 && str[i] != ' ' && count < 0)
		{
			count = i;
		}
		else if (((str[i] == '\"' && count_d >= 0)
			|| (str[i] == '\'' && count_s >= 0))
			&& open)
		{
			if (count_s > 0)
			{
				new[j] = split_words(str, count_s, i + 1);
				count_s = -1;
			}
			else if (count_d > 0)
			{
				new[j] = split_words(str, count_d, i + 1);
				count_d = -1;
			}
			j++;
			open = 0;
		}
		else if ((str[i] == ' ' || i == len || str[i] == '\"')
				 && open == 0 && count >= 0)
		{
			new[j] = split_words(str, count, i);
			count = -1;
			j++;
			if ((str[i] == '\"' || str[i] == '\'') && open == 0 && count < 0)
			{
				if (str[i] == '\'')
				{
					count_s = i;
					open = 1;
				}
				else if (str[i] == '\"')
				{
					count_d = i;
					open = 2;
				}
			}
		}
		i++;
	}
	new[j] = 0;
	return (new);
}
