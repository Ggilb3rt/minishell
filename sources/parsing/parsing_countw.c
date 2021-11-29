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

static int	count_open_quote(t_split *split, t_list_envp *ms_env)
{
	int	count;

	count = 0;
	while (close_quote(split))
	{
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

static int	continue_count(t_split *split, int count, t_list_envp *ms_env)
{
	if (split->str[split->i] == '>' || split->str[split->i] == '<')
		skip_redir(split);
	else if (!search_var(split, ms_env, 0, NULL))
	{
		split->i++;
		count++;
		if (split->str[split->i] == ' ')
			return (count);
	}
	else
	{
		count += split->q;
		if (split->str[split->i] == ' ')
			return (count);
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
			count += continue_count(&split, count, ms_env);
	}
	free(cur);
	cur = NULL;
	return (count);
}
