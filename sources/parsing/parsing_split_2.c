/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_split_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alangloi <alangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 16:09:29 by alangloi          #+#    #+#             */
/*   Updated: 2021/11/09 15:38:23 by alangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Theses function (and the other functions of the file) will count the
 * different parts of the parsing for allocating the right amount of space
 * before the storage into a new array of words.
 */

static void	check_quote(char c, t_count *cnt)
{
	if (c == '\'')
		cnt->open = 1;
	else if (c == '\"')
		cnt->open = 2;
	else
		cnt->open = 0;
}

static int	go_next_quote(char *str, t_count *cnt)
{
	char	c;

	c = 0;
	if (cnt->open == 1)
		c = '\'';
	else if (cnt->open == 2)
		c = '\"';
	while (str[cnt->i] != c)
	{
		if (str[cnt->i] == '\0')
			return (0);
		cnt->i++;
	}
	return (cnt->i);
}

static void	meet_quote(char *str, t_count *cnt)
{
	int	jmp;

	cnt->i++;
	jmp = go_next_quote(str, cnt);
	if (jmp > 0)
	{
		cnt->i = jmp;
		cnt->open = 0;
	}
	else
		perror("error next quote\n");
}

static void	trig_words(char *str, t_count *cnt)
{
	check_quote(str[cnt->i], cnt);
	if (cnt->open)
	{
		meet_quote(str, cnt);
		cnt->words++;
		if (ft_isalpha(str[cnt->i + 1]))
			cnt->trig = 0;
	}
	else if ((str[cnt->i] != ' ' && !cnt->open) && cnt->trig == 0)
	{
		cnt->trig = 1;
		cnt->words++;
	}
	else if (str[cnt->i] == ' ')
		cnt->trig = 0;
	cnt->i++;
}

int	word_count(char *str)
{
	t_count	cnt;

	cnt.open = 0;
	cnt.i = 0;
	cnt.words = 0;
	cnt.trig = 0;
	while (str[cnt.i])
		trig_words(str, &cnt);
	return (cnt.words);
}
