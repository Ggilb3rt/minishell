/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_countw.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alangloi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 17:37:22 by alangloi          #+#    #+#             */
/*   Updated: 2021/11/29 17:37:24 by alangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_into_quote(t_split *split, t_list_envp *ms_env, int *count)
{
	if (split->str[split->i])
	{
		if (!split->open_s && split->open_d)
		{
			if (!search_var(split, ms_env, 0, NULL))
			{
				*count += 1;
				split->i++;
			}
			else
				*count += split->q;
		}
		else
		{
			split->i++;
			*count += 1;
		}
		return (1);
	}
	else
		return (0);
}

static int	count_open_quote(t_split *split, t_list_envp *ms_env, int *count)
{
	if (split->str[split->i])
	{
		while (close_quote(split))
		{
			if (!count_into_quote(split, ms_env, count))
				return (0);
		}
	}
	else
		return (0);
	return (1);
}

static int	continue_count(t_split *split, t_list_envp *ms_env, int *count)
{
	if (split->str[split->i] == '>' || split->str[split->i] == '<')
		skip_count(split, NULL);
	else if (!search_var(split, ms_env, 0, NULL))
	{
		split->i++;
		*count += 1;
		if (split->str[split->i] == ' ')
			return (0);
	}
	else
		*count += split->q;
	return (1);
}

static int	count_ret(t_split *split, t_list_envp *ms_env, int *count)
{
	if (open_quote(split))
	{
		if (!count_open_quote(split, ms_env, count))
			return (0);
	}
	else
	{
		if (!continue_count(split, ms_env, count))
			return (0);
	}
	return (1);
}

int	count_word(char *str, t_list_envp *ms_env, int pos)
{
	int			count;
	t_split		split;

	count = 0;
	init_split(&split, str);
	split.i = pos;
	while (split.str[split.i])
	{
		if (!count_ret(&split, ms_env, &count))
			break ;
	}
	printf("count word\t%d\n", count);
	return (count);
}
