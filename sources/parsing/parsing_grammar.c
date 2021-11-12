/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_grammar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 14:22:04 by alangloi          #+#    #+#             */
/*   Updated: 2021/10/29 16:51:27 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	redir_great(t_simple_command *cur, t_command *cmd)
{
	if (cur->token == GREAT)
	{
		//free(cmd->out_file);
		//cmd->out_file = NULL;
		if (ft_str_isalnum_under(cur->arg[1]))
			cmd->out_file = ft_strdup(cur->arg[1]);
		else
			printf("unexpected syntax\n");
	}
	else if (cur->token == DGREAT)
	{
		//free(cmd->out_file);
		//cmd->out_file = NULL;
		if (ft_str_isalnum_under(cur->arg[1]))
			cmd->out_file = ft_strdup(cur->arg[1]);
		else
			printf("unexpected syntax\n");
	}
}

static void	redir_less(t_simple_command *cur, t_command *cmd)
{
	if (cur->token == LESS)
	{
		//free(cmd->in_file);
		//cmd->in_file = NULL;
		if (ft_str_isalnum_under(cur->arg[1]))
			cmd->in_file = ft_strdup(cur->arg[1]);
		else
			printf("unexpected syntax\n");
	}
	else if (cur->token == DLESS)
	{
		//free(cmd->in_file);
		//cmd->in_file = NULL;
		if (ft_str_isalnum_under(cur->arg[1]))
			cmd->end = cur->arg[1];
		else
			printf("unexpected syntax\n");
		g_ret = EHERE;
	}
}

static void	io_redirections(t_command *cmd)
{
	t_simple_command	*cur;

	cur = (*cmd->list);
	while (cur)// && cur->next != NULL)
	{
		if (cur->token == GREAT || cur->token == DGREAT)
			redir_great(cur, cmd);
		else if (cur->token == LESS || cur->token == DLESS)
			redir_less(cur, cmd);
		cur = cur->next;
	}
}

int	parser(t_command **cmd)
{
	t_command	*cur;

	cur = *cmd;
	while (cur)// && cur->next != NULL)
	{
		io_redirections(cur);
		cur = cur->next;
	}
	return (1);
}
