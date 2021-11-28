/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_count.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alangloi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 14:34:03 by alangloi          #+#    #+#             */
/*   Updated: 2021/11/26 14:34:04 by alangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_check_args(t_split *split)
{
	int	count;

	count = 0;
	if (open_quote(split))
	{
		while (close_quote(split))
			split->i++;
		/*
		if (split->open_d || split->open_s)
		{
			printf("minishell: abuse pas stp, ferme tes quotes\n");
		}
		 */
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
		split->i++;
	return (count);
}

int	count_args(char *str, int pos)
{
	t_split	split;
	int		count;

	count = 0;
	init_split(&split, str);
	split.i = pos;
	while (split.str[split.i] && split.str[split.i] != '|')
		count += count_check_args(&split);
	count++;
	return (count);
}

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

int	count_word(char *str, t_list_envp *ms_env, int pos)
{
	int			count;
	t_split		split;
	t_command	*cur;

	count = 0;
	init_split(&split, str);
	//printf("init count\n");
	cur = alloc_command(NULL);
	split.i = pos;
	while (split.str[split.i] && split.str[split.i] != ' ')
	{
		if (open_quote(&split))
			count += count_open_quote(&split, ms_env);
		else
		{
			redirection(&split, &cur, ms_env);
			if (!search_var(&split, ms_env, 0, NULL))
			{
				split.i++;
				count++;
			}
			else
				count += split.q;
		}
	}
	//printf("free count\n");
	//printf("free *cmd %p\n", cur);
	free(cur);
	cur = NULL;
	return (count);
}
