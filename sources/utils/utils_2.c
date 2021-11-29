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
	int	len;

	i = 0;
	len = array_size(arr);
	while (i < len)
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}

void	free_tab_2(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
}

void	free_command(t_command **cmd)
{
	t_command	*cur;
	t_command	*tmp;

	cur = *cmd;
	while (cur)
	{
		tmp = cur;
		cur = cur->next;
		free(tmp);
		tmp = NULL;
	}
	free(cmd);
	cmd = NULL;
}

void	free_all(t_command **cmd)
{
	t_command	*cur;

	if (cmd)
	{
		cur = *cmd;
		while (cur)
		{
			if (cur->arg)
				free_tab(cur->arg);
			cur = cur->next;
		}
		free_command(cmd);
	}
}
