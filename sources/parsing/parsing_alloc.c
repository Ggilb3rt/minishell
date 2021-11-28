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
	int len;

	len = count_word(split->str, ms_env, split->i) + 1;
	//printf("alloc word\n");
	split->new[split->o] = malloc (sizeof(char)
			* (len));
	//printf("create arg[i] %p\n", split->new[split->o]);
	printf("nb word %d\n", len);
	if (!split->new[split->o])
		return (0);
	split->open_d = 0;
	split->open_s = 0;
	return (1);
}

int	alloc_arg(t_split *split)
{
	int len;

	len = count_args(split->str, split->i) + 1;
	split->new = malloc(sizeof(char *) * (len));
	printf("nb arg %d\n", len);
	//printf("create arg %p\n", split->new);
	if (!split->new)
		return (0);
	split->new[split->o] = NULL;
	return (1);
}

t_command	*alloc_command(char **arg)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	//printf("create *cmd %p\n", cmd);
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
