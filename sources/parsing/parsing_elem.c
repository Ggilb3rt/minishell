/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_elem.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alangloi <alangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 14:16:40 by alangloi          #+#    #+#             */
/*   Updated: 2021/10/19 14:29:39 by alangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	*list_last(t_simple_command *list)
{
	if (!list)
		return (NULL);
	while (list->next != NULL)
		list = list->next;
	return (list);
}

void	add_elem(t_simple_command *new, t_simple_command **list)
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
		cur = list_last(*list);
		cur->next = new;
		cur->next->next = NULL;
	}
}

t_simple_command	*alloc_elem(char **str)
{
	t_simple_command	*new;

	new = malloc(sizeof(t_simple_command));
	if (!new)
		return (NULL);
	new->arg = str;
	new->token = create_token(new->arg[0]);
	new->numb_avail = 0;
	new->numb = 0;
	new->next = NULL;
	return (new);
}

void	add_newline(t_simple_command **list, char **arg, int i)
{
	t_simple_command	*new;
	char				**arr;

	arr = malloc(sizeof(char *));
	arr[0] = "/";
	if (arg[i] == NULL)
	{
		new = alloc_elem(arr);
		add_elem(new, list);
	}
}
