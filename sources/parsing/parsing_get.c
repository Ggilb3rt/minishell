/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alangloi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 14:35:24 by alangloi          #+#    #+#             */
/*   Updated: 2021/11/26 14:35:26 by alangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_char(t_split *split)
{
	split->new[split->o][split->l] = split->str[split->i];
	split->l++;
	split->i++;
}

void	get_arg(t_split *split, t_command **cur, t_command **cmd)
{
	split->new[split->o][split->l] = '\0';
	split->new[split->o + 1] = NULL;
	dup_quotes(split->new);
	(*cur)->arg = split->new;
	(*cur)->token = create_token((*cur)->arg[0]);
	add_command(cur, cmd);
	*cur = NULL;
}

int	get_arg_pipe(t_split *split, t_command **cur, t_command **cmd)
{
	split->i++;
	del_spaces(split);
	get_arg(split, cur, cmd);
	if (!split->str[split->i])
	{
		printf("minishell: don't mess with my heart.\n");
		return (-1);
	}
	if (split->str[split->i] == '|')
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (-1);
	}
	return (1);
}

int	get_word(t_split *split, t_list_envp *ms_env)
{
	split->new[split->o][split->l] = '\0';
	split->l = 0;
	split->o++;
	if (!alloc_word(split, ms_env))
		return (0);
	return (1);
}

int	get_word_space(t_split *split, t_list_envp *ms_env)
{
	split->i++;
	del_spaces(split);
	if (split->str[split->i] == '|')
		return (1);
	if (!split->str[split->i])
		return (0);
	if (split->str[split->i] == '>' || split->str[split->i] == '<')
		return (1);
	if (!get_word(split, ms_env))
		return (0);
	return (1);
}
