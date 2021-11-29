/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_count.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 14:34:03 by alangloi          #+#    #+#             */
/*   Updated: 2021/11/28 16:26:01 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_into_quote(t_split *split)
{
	if (split->str[split->i])
	{
		while (close_quote(split))
		{
			split->i++;
			if (!split->str[split->i])
				return (0);
		}
	}
	else
		return (0);
	return (1);
}

void skip_count(t_split *split)
{
	while (split->str[split->i] == '<' || split->str[split->i] == '>'
		   || split->str[split->i] == ' ')
		split->i++;
	while (split->str[split->i] && split->str[split->i] != ' ')
		split->i++;
}

static void	count_not(t_split *split)
{
	if (split->str[split->i] == '>' || split->str[split->i] == '<')
		skip_count(split);
	else
		split->i++;
}

static int	count_check_args(t_split *split, int *count)
{
	if (open_quote(split))
	{
		if (!count_into_quote(split))
			return (0);
	}
	else if (split->str[split->i] == ' ')
	{
		split->i++;
		del_spaces(split);
		if (!split->str[split->i] || split->str[split->i] == '|')
			return (0);
		*count += 1;
	}
	else
		count_not(split);
	return (1);
}

int	count_args(char *str, int pos)
{
	t_split		split;
	int			count;

	count = 0;
	init_split(&split, str);
	split.i = pos;
	while (split.str[split.i] && split.str[split.i] != '|')
	{
		if (!count_check_args(&split, &count))
			break ;
	}
	count++;
	//printf("count arg\t%d\n", count);
	return (count);
}
