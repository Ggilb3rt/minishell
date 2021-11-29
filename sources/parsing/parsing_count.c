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

static int	count_check_args(t_split *split, t_command **cur)
{
	int	count;

	(void)cur;
	count = 0;
	if (open_quote(split))
	{
		while (close_quote(split))
		{
			split->i++;
			if (!split->str[split->i])
			{
				return (0);
			}

		}
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
	{
		if (split->str[split->i] == '>' || split->str[split->i] == '<')
		{
			while (split->str[split->i] == '<' || split->str[split->i] == '>'
				|| split->str[split->i] == ' ')
			{
				split->i++;
			}
			while (split->str[split->i] != ' ')
			{
				split->i++;
			}
		}
		else
			split->i++;
	}
	return (count);
}

int	count_args(char *str, int pos)
{
	t_split	split;
	int		count;
	t_command *cur;

	cur = alloc_command(NULL);
	count = 0;
	init_split(&split, str);
	split.i = pos;
	while (split.str[split.i] && split.str[split.i] != '|')
	{
		count += count_check_args(&split, &cur);
	}
	count++;
	free(cur);
	cur = NULL;
	return (count);
}

static int	count_open_quote(t_split *split, t_list_envp *ms_env)
{
	int	count;

	count = 0;
	while (close_quote(split))
	{
		if (!split->str[split->i])
			return (0);
		if (!split->open_s && split->open_d)
		{
			if (!search_var(split, ms_env, 0, NULL))
			{
				count++;
				split->i++;
			}
			else
				count += split->q;
		}
		else
		{
			split->i++;
			count++;
		}
	}
	return (count);
}

int	count_word(char *str, t_list_envp *ms_env, int pos)
{
	int			count;
	t_split		split;
	t_command	*cur;

	count = 0;
	init_split(&split, str);
	cur = alloc_command(NULL);
	split.i = pos;
	while (split.str[split.i])
	{
		if (open_quote(&split))
		{
			count += count_open_quote(&split, ms_env);
			if (split.str[split.i] == ' ')
				return (count);
		}
		else
		{
			if (split.str[split.i] == '>' || split.str[split.i] == '<')
			{
				while (split.str[split.i] == '<' || split.str[split.i] == '>'
					   || split.str[split.i] == ' ')
				{
					split.i++;
				}
				while (split.str[split.i] != ' ')
				{
					split.i++;
				}
			}
			else if (!search_var(&split, ms_env, 0, NULL))
			{
				split.i++;
				count++;
				if (split.str[split.i] == ' ')
					return (count);
			}
			else
			{
				count += split.q;
				if (split.str[split.i] == ' ')
					return (count);
			}
		}
	}
	free(cur);
	cur = NULL;
	return (count);
}
