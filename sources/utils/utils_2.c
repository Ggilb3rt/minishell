/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alangloi <alangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 14:09:16 by alangloi          #+#    #+#             */
/*   Updated: 2021/10/19 14:10:03 by alangloi         ###   ########.fr       */
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

static void 	free_simple_command(t_simple_command **list)
{
	int 				i;
	int 				size;

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
}