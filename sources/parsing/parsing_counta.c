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

void	skip_redir(t_split *split)
{
	while (split->str[split->i] == '<' || split->str[split->i] == '>'
		|| split->str[split->i] == ' ')
		split->i++;
	while (split->str[split->i] != ' ')
		split->i++;
}

static int	count_into_quote(t_split *split)
{
	while (close_quote(split))
	{
		split->i++;
		if (!split->str[split->i])
			return (0);
	}
	return (1);
}

static void	count_not(t_split *split)
{
	if (split->str[split->i] == '>' || split->str[split->i] == '<')
		skip_redir(split);
	else
		split->i++;
}

static int	count_check_args(t_split *split, t_command **cur)
{
	int	count;

	(void)cur;
	count = 0;
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
			return (count);
		count++;
	}
	else
		count_not(split);
	return (count);
}

int	count_args(char *str, int pos)
{
	t_split		split;
	int			count;
	t_command	*cur;

	cur = alloc_command(NULL);
	count = 0;
	init_split(&split, str);
	split.i = pos;
	while (split.str[split.i] && split.str[split.i] != '|')
		count += count_check_args(&split, &cur);
	count++;
	free(cur);
	cur = NULL;
	return (count);
}
