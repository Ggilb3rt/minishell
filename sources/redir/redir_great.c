/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_great.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alangloi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 17:35:44 by alangloi          #+#    #+#             */
/*   Updated: 2021/11/29 17:35:45 by alangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exit_redir(t_split *split)
{
	del_spaces(split);
	if (split->str[split->i] == '|')
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (-1);
	}
	if (split->str[split->i] == '<' || split->str[split->i] == '>')
	{
		printf("bash: syntax error near unexpected token `>'\n");
		return (-1);
	}
	if (!split->str[split->i])
	{
		printf("bash: syntax error near unexpected token `newline'\n");
		return (-1);
	}
	return (1);
}

static void	check_file(t_command **cur)
{
	if ((*cur)->out_file)
	{
		free((*cur)->out_file);
		(*cur)->out_file = NULL;
	}
}

int	redir_great(t_split *split, t_command **cur, t_list_envp *ms_env)
{
	split->red = 0;
	split->i++;
	if (exit_redir(split) == -1)
		return (-1);
	check_file(cur);
	(*cur)->out_file = malloc(sizeof(char) * (ret_val(split, ms_env, 0) + 1));
	if (!(*cur)->out_file)
		return (0);
	split->open_d = 0;
	split->open_s = 0;
	while (split->str[split->i])
	{
		if (!get_string(split, ms_env, cur, 2))
			break ;
	}
	(*cur)->token_in = 0;
	(*cur)->token_out = GREAT;
	(*cur)->out_file[split->red] = '\0';
	init_out_file_fd((*cur)->token_out, (*cur)->out_file, &(*cur)->fd_out);
	return (1);
}
