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

static void	redir_great(t_simple_command **lst, t_command *cmd)
{
	if ((*lst)->next->token == GREAT)
	{
		free(cmd->out_file);
		cmd->out_file = NULL;
		cmd->out_file = ms_strdup((*lst)->next->next->arg[0]);
	}
	if ((*lst)->next->token == DGREAT)
	{
		free(cmd->out_file);
		cmd->out_file = NULL;
		cmd->out_file = ms_strdup((*lst)->next->next->arg[0]);
	}
}

static void	redir_less(t_simple_command **lst, t_command *cmd)
{
	if ((*lst)->next->token == LESS)
	{
		free(cmd->in_file);
		cmd->in_file = NULL;
		cmd->in_file = ms_strdup((*lst)->next->next->arg[0]);
	}
	if ((*lst)->next->token == DLESS)
	{
		free(cmd->in_file);
		cmd->in_file = NULL;
		cmd->in_file = ms_strdup((*lst)->next->next->arg[0]);
	}
}

static void	io_redirections(t_command *cmd)
{
	t_simple_command	**lst;

	lst = cmd->list;
	while (*lst != NULL)
	{
		if ((*lst)->token == WORD)
		{
			if ((*lst)->next->token == PIPE)
				*lst = (*lst)->next;
			redir_less(lst, cmd);
			redit_great(lst, cmd);
		}
		*lst = (*lst)->next;
	}
}

int	parser(t_command *cmd)
{
	io_redirections(cmd);
	return (1);
}
