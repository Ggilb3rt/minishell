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
		cur = *list;
		while (cur && cur->next != NULL)
			cur = cur->next;
		cur->next = new;
		//cur->next->next = NULL;
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
		cur = *cmd;
		while (cur && cur->next != NULL)
			cur = cur->next;
		cur->next = new;
		//cur->next->next = NULL;
	}
}

int	add_newline(t_command **list, char **arg, int i)
{
	t_command	*new;
	char		**arr;

	arr = malloc(sizeof(char *));
	if (!arr)
		return (0);
	arr[0] = "/";
	if (arg[i] == NULL)
	{
		new = alloc_command(arr, 0, 1);
		add_command(new, list);
	}
	return (1);
}
