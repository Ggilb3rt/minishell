/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_grammar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alangloi <alangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 14:22:04 by alangloi          #+#    #+#             */
/*   Updated: 2021/10/19 14:28:02 by alangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	redir_great(t_simple_command *cur, t_command *cmd)
{
	(void)g_ret;
	if (cur->next->token == GREAT && cur->next->next->token == WORD)
	{
		free(cmd->out_file);
		cmd->out_file = NULL;
		cmd->out_file = ft_strdup(cur->next->next->arg[0]);
	}
	else if (cur->next->token == DGREAT && cur->next->next->token == WORD)
	{
		free(cmd->out_file);
		cmd->out_file = NULL;
		cmd->out_file = ft_strdup(cur->next->next->arg[0]);
	}
}

static void	redir_less(t_simple_command *cur, t_command *cmd)
{
	if (cur->next->token == LESS && cur->next->next->token == WORD)
	{
		free(cmd->in_file);
		cmd->in_file = NULL;
		cmd->in_file = ft_strdup(cur->next->next->arg[0]);
	}
	else if (cur->next->token == DLESS && cur->next->next->token == WORD)
	{
		free(cmd->in_file);
		cmd->in_file = NULL;
		cmd->end = cur->next->next->arg[0];
		g_ret = EHERE;
	}
}

static void	io_redirections(t_command *cmd)
{
	t_simple_command	*cur;

	cur = (*cmd->list);
	while (cur->next != NULL)
	{
		if (cur->token == WORD)
		{
			if (cur->next->token == GREAT || cur->next->token == DGREAT)
				redir_great(cur, cmd);
			else if (cur->next->token == LESS || cur->next->token == DLESS)
				redir_less(cur, cmd);
		}
		cur = cur->next;
	}
}

int	parser(t_command **cmd)
{
	t_command	*cur;

	cur = *cmd;
	while (cur != NULL)
	{
		io_redirections(cur);
		if (cur->next != NULL && (*cur->next->list)->token != NWLINE)
		{
			//cur->fd_out = open(cur->out_file, );
			//cur->next->fd_in = cur;
		}
		cur = cur->next;
	}
	return (1);
}
