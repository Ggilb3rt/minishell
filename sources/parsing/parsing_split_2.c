/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_split_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alangloi <alangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 16:09:29 by alangloi          #+#    #+#             */
/*   Updated: 2021/10/20 16:09:32 by alangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_quote(char c)
{
	if (c == '\'')
		return (1);
	else if (c == '\"')
		return (2);
	else
		return (0);
}

static int	go_next_quote(char *str, int i, int open)
{
	char	c;

	c = 0;
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

static int	meet_quote(char *str, int i, int *open)
{
	int	jmp;

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
/*
static int	check_open(int *open, int *trig, char *str, int i)
{
	if (*open)
	{
		i = meet_quote(str, i, open);
		if (ms_is_alpha(&str[i + 1]))
			*trig = 0;
		return (1);
	}
	else if ((str[i] != ' ' && !*open) && *trig == 0)
	{
		*trig = 1;
		return (1);
	}
	else if (str[i] == ' ')
		*trig = 0;
	return (0);
}
*/
int	word_count(char *str)
{
	int	words;
	int	trig;
	int	i;
	int	open;

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

		/*
		open = check_quote(str[i]);
		words += check_open(&open, &trig, str, i);
		 */
		i++;
	}
	return (words);
}
