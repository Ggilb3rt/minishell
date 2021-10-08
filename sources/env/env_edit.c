/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_edit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 16:17:57 by ggilbert          #+#    #+#             */
/*   Updated: 2021/10/08 08:46:56 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_lst_push_end(t_list_envp **alst, t_list_envp *new)
{
	t_list_envp	*last;

	last = NULL;
	if (!alst)
		return ;
	if (!*alst)
		*alst = new;
	else if (alst && *alst)
	{
		last = *alst;
		while (last->next)
			last = last->next;
		last->next = new;
	}
}

int	ms_lst_pop_end(t_list_envp *head)
{
	t_list_envp	*current;
	t_list_envp	*tmp;

	if (!head)
		return (0);
	if (head->next == NULL)
	{
		remove_lst_content(head->content);
		free(head);
		head = NULL;
		return (0);
	}
	current = head;
	while (current->next->next != NULL)
		current = current->next;
	tmp = current;
	current = current->next;
	remove_lst_content(current->content);
	free(current);
	tmp->next = NULL;
	return (1);
}

void	edit_lst_content(t_list_envp *env, int index, char *new_val)
{
	int			i;
	t_list_envp	*tmp;

	i = 1;
	tmp = env;
	while (i++ < index)
		tmp = tmp->next;
	tmp = tmp->next;
	free(tmp->content);
	tmp->content = ms_strdup(new_val);
}

t_list_envp	*ms_lst_pop_first(t_list_envp *head)
{
	t_list_envp	*tmp;

	tmp = head;
	head = head->next;
	remove_lst_content(tmp->content);
	free(tmp);
	return (head);
}

void	ms_lst_pop_inside(t_list_envp *current, t_list_envp *prev)
{
	t_list_envp	*tmp;

	if (!current)
		return ;
	if (!prev)
		return ;
	if (current == prev)
	{
		current = ms_lst_pop_first(current);
		return ;
	}
	tmp = current;
	prev->next = current->next;
	remove_lst_content(tmp->content);
	free(tmp);
	tmp = NULL;
}
