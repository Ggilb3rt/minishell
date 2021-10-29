/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_add.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alangloi <alangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 11:02:15 by alangloi          #+#    #+#             */
/*   Updated: 2021/10/28 11:02:19 by alangloi         ###   ########.fr       */
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

static t_simple_command	*simple_last(t_simple_command *list)
{
	if (!list)
		return (NULL);
	while (list->next != NULL)
		list = list->next;
	return (list);
}

void	add_simple(t_simple_command *new, t_simple_command **list)
{
	t_simple_command	*cur;

	if (!new)
		return ;
	new->next = NULL;
	if (!*list)
	{
		new->next = *list;
		*list = new;
	}
	else
	{
		cur = simple_last(*list);
		cur->next = new;
		cur->next->next = NULL;
	}
}

void	add_command(t_command *new, t_command **cmd)
{
	t_command	*cur;

	if (!new)
		return ;
	new->next = NULL;
	if (!*cmd)
	{
		new->next = *cmd;
		*cmd = new;
	}
	else
	{
		cur = command_last(*cmd);
		cur->next = new;
		cur->next->next = NULL;
	}
}

void	add_newline(t_command **list, char **arg, int i)
{
	t_command	*new;
	char		**arr;

	arr = malloc(sizeof(char *));
	arr[0] = "/";
	if (arg[i] == NULL)
	{
		new = alloc_command(arr, 0, 1);
		add_command(new, list);
	}
}
