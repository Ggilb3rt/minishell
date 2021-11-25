/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_alloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 14:16:40 by alangloi          #+#    #+#             */
/*   Updated: 2021/10/29 16:51:03 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int alloc_word(t_split *split, t_list_envp *ms_env)
{
	split->new[split->o] = malloc (sizeof(char) * (count_word(split->str, ms_env, split->i) + 1));
	if (!split->new[split->o])
		return (0);
	return (1);
}

int alloc_arg(t_split *split)
{
	split->new = malloc(sizeof(char *) * (count_args(split->str, split->i) + 1));
	if (!split->new)
		return (0);
	split->new[split->o] = NULL;
	return (1);
}

t_command	*alloc_command(char **arg)
{
	t_command	*cmd;

	//(void)arg;
	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	//cmd->numb_avail_simple_commands = 0;
	//cmd->numb_simple_commands = 0;
	cmd->arg = arg; //get_simple(arg);
	cmd->out_file = NULL;
	cmd->in_file = NULL;
	cmd->end = NULL;
	//cmd->err_file = NULL;
	cmd->build = -1;
	cmd->token_in = -1;
	cmd->token_out = -1;
	cmd->fd_out = -1;
	cmd->fd_in = -1;
	cmd->next = NULL;
	return (cmd);
}
