/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_add.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alangloi <alangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 11:02:15 by alangloi          #+#    #+#             */
/*   Updated: 2021/11/09 16:23:41 by alangloi         ###   ########.fr       */
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
	int tmp;

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

	//printf("init newline\n");
	new = alloc_command(NULL);
	new->arg = malloc(sizeof(char *) * 2);
	//printf("create arg %p\n", new->arg);
	new->arg[0] = malloc(sizeof(char) * 2);
	//printf("create arg[i] %p\n", new->arg[0]);
	new->arg[0][0] = '/';
	new->arg[0][1] = '\0';
	//new->arg[1] = malloc(sizeof(char));
	//printf("create arg[i] %p\n", new->arg[1]);
	new->arg[1] = NULL;
	//printf("create arg[i] %p\n", new->arg[1]);
	new->token = create_token(new->arg[0]);
	add_command(&new, cmd);
	//free(new->arg[0]);
	//free(new->arg);
	return (1);
}
