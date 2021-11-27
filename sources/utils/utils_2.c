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
	t_command *tmp;

	if (*list)
	{
		while (*list != NULL)
		{
			tmp = *list;
			*list = (*list)->next;
			if (tmp->arg)
			{
				i = 0;
				size = array_size(tmp->arg);
				while (i < size)
				{
					free(tmp->arg[i]);
					tmp->arg[i] = NULL;
					i++;
				}
				free(tmp->arg);
				tmp->arg = NULL;
			}
			if (tmp->out_file)
			{
				free(tmp->out_file);
				tmp->out_file = NULL;
			}
			if (tmp->in_file)
			{
				free(tmp->in_file);
				tmp->in_file = NULL;
			}
			if (tmp->end)
			{
				free(tmp->end);
				tmp->end = NULL;
			}
			free(tmp);
			tmp = NULL;
		}
		free(*list);
		*list = NULL;
	}
}
/*
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
*/