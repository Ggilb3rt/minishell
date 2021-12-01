/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_alloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 14:16:40 by alangloi          #+#    #+#             */
/*   Updated: 2021/11/28 17:35:10 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	alloc_word(t_split *split, t_list_envp *ms_env)
{
	split->new[split->o] = malloc (sizeof(char)
			* (count_word(split->str, ms_env, split->i) + 1));
	if (!split->new[split->o])
		return (0);
	split->new[split->o][0] = '\0';
	split->open_d = 0;
	split->open_s = 0;
	return (1);
}

int	alloc_arg(t_split *split)
{
	split->new = malloc(sizeof(char *)
			* (count_args(split->str, split->i) + 1));
	if (!split->new)
		return (0);
	split->new[split->o] = NULL;
	return (1);
}

t_command	*alloc_command(char **arg)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	if (arg)
		cmd->arg = arg;
	cmd->out_file = NULL;
	cmd->in_file = NULL;
	cmd->end = NULL;
	cmd->build = -1;
	cmd->token_in = -1;
	cmd->token_out = -1;
	cmd->fd_out = -1;
	cmd->fd_in = -1;
	cmd->fd_heredoc = -1;
	cmd->can_exec = -1;
	cmd->next = NULL;
	return (cmd);
}
