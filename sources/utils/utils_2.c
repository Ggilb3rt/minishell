/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 14:09:16 by alangloi          #+#    #+#             */
/*   Updated: 2021/11/22 17:10:04 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}
/*
void free_command(t_command **cmd)
{
	while ((*cmd)->next)
	{
		free(*cmd);
		*cmd = NULL;
		(*cmd) = (*cmd)->next;
	}
	free(cmd);
	cmd = NULL;
}

void free_simple(t_simple_command **list)
{
	while ((*list)->next)
	{
		free(*list);
		*list = NULL;
		(*list) = (*list)->next;
	}
	free(list);
	list = NULL;
}

void	free_command(t_command *cmd)
{
	while (cmd->list != NULL)
	{
		free_simple_command(cmd->list);
		free(cmd->list);
		cmd->list = NULL;
		cmd->list = cmd->list->next;
	}
}
*/

void 	free_command(t_command **list)
{
	int	i;
	int	size;

	while ((*list) && (*list)->next)
	{
		size = array_size((*list)->arg);
		i = 0;
		while (i < size)
		{
			free((*list)->arg[i]);
			(*list)->arg[i] = NULL;
			i++;
		}
		free((*list)->arg);
		(*list)->arg = NULL;
		*list = (*list)->next;
	}
	free(list);
	list = NULL;
}
/*
void	free_command(t_command **cmd)
{
	while (*cmd && (*cmd)->next)
	{
		free_simple_command((*cmd)->list);
		free(*cmd);
		(*cmd) = (*cmd)->next;
	}
	free(cmd);
	cmd = NULL;
}*/
