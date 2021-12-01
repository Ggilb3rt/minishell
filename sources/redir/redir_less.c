/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_less.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alangloi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 17:35:56 by alangloi          #+#    #+#             */
/*   Updated: 2021/11/29 17:35:57 by alangloi         ###   ########.fr       */
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
		printf("bash: syntax error near unexpected token `<'\n");
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
	if ((*cur)->in_file)
	{
		free((*cur)->in_file);
		(*cur)->in_file = NULL;
	}
}

int	redir_less(t_split *split, t_command **cur, t_list_envp *ms_env)
{
	split->red = 0;
	split->i++;
	if (exit_redir(split) == -1)
		return (-1);
	check_file(cur);
	(*cur)->in_file = malloc(sizeof(char) * (ret_val(split, ms_env, 0) + 1));
	if (!(*cur)->in_file)
		return (0);
	split->open_d = 0;
	split->open_s = 0;
	while (split->str[split->i])
	{
		if (!get_string(split, ms_env, cur, 3))
			break ;
	}
	(*cur)->token_in = LESS;
	(*cur)->token_out = 0;
	(*cur)->in_file[split->red] = '\0';
	init_in_file_fd((*cur)->token_in,
		(*cur)->in_file, &(*cur)->fd_in, &(*cur)->fd_heredoc);
	return (1);
}
