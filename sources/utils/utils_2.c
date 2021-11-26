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

void	free_command(t_command **list)
{
	int	i;
	int	size;
	t_command *cur;

	cur = *list;
	while (cur)
	{
		size = array_size(cur->arg);
		i = 0;
		while (i < size)
		{
			free(cur->arg[i]);
			cur->arg[i] = NULL;
			i++;
		}
		if (cur->out_file)
			free(cur->out_file);
		if (cur->in_file)
			free(cur->in_file);
		if (cur->end)
			free(cur->end);
		free(cur->arg);
		cur->arg = NULL;
		cur = cur->next;
	}
	while (*list)
	{
		free(*list);
		*list = NULL;
	}
	free(list);
	list = NULL;
}

void	free_split(t_split *split)
{
	int	i;

	i = 0;
	if (split->new)
	{
		while (split->new[i])
		{
			free(split->new[i]);
			split->new[i] = NULL;
			i++;
		}
		free(split->new);
		split->new = NULL;
	}
}
