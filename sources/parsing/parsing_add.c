/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_add.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 11:02:15 by alangloi          #+#    #+#             */
/*   Updated: 2021/11/28 16:23:50 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_command	*command_last(t_command *cmd)
{
	if (!cmd)
		return (NULL);
	while (cmd->next != NULL)
		cmd = cmd->next;
	return (cmd);
}

void	add_command(t_command **new, t_command **cmd)
{
	t_command	*cur;
	int			tmp;

	if (!*new)
		return ;
	(*new)->next = NULL;
	if (!*cmd)
	{
		(*new)->next = *cmd;
		*cmd = *new;
		(*cmd)->nb_cmd = 1;
	}
	else
	{
		tmp = (*cmd)->nb_cmd;
		cur = command_last(*cmd);
		(*new)->nb_cmd = tmp + 1;
		cur->next = *new;
		cur->next->next = NULL;
	}
}

int	add_newline(t_command **cmd)
{
	t_command	*new;

	new = alloc_command(NULL);
	new->arg = malloc(sizeof(char *) * 2);
	new->arg[0] = malloc(sizeof(char) * 2);
	new->arg[0][0] = '/';
	new->arg[0][1] = '\0';
	new->arg[1] = NULL;
	new->token = create_token(new->arg[0]);
	add_command(&new, cmd);
	return (1);
}
