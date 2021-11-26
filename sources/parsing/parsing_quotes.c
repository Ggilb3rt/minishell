/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alangloi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 14:34:17 by alangloi          #+#    #+#             */
/*   Updated: 2021/11/26 14:34:19 by alangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_quote(t_split *split)
{
	if (split->str[split->i] == '\"' && !split->open_s && !split->open_d)
	{
		split->open_d = 1;
		split->i++;
		return (1);
	}
	if (split->str[split->i] == '\'' && !split->open_d && !split->open_s)
	{
		split->open_s = 1;
		split->i++;
		return (1);
	}
	return (0);
}

int	close_quote(t_split *split)
{
	if (split->str[split->i] == '\"' && !split->open_s && split->open_d)
	{
		split->open_d = 0;
		split->i++;
		return (0);
	}
	if (split->str[split->i] == '\'' && !split->open_d && split->open_s)
	{
		split->open_s = 0;
		split->i++;
		return (0);
	}
	return (1);
}

void	into_quote(t_split *split, t_list_envp *ms_env)
{
	while (close_quote(split))
	{
		if (!split->open_s && split->open_d)
		{
			if (!search_var(split, ms_env, 1, NULL))
				get_char(split);
		}
		else
			get_char(split);
	}
}

void	dup_quotes(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		if (!ft_strcmp(arr[i], " "))
		{
			free(arr[i]);
			arr[i] = ft_strdup("");
		}
		i++;
	}
}
