/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_edit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 16:17:57 by ggilbert          #+#    #+#             */
/*   Updated: 2021/10/07 14:40:45 by ggilbert         ###   ########.fr       */
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

void	remove_lst_content(char *content)
{
	if (content != NULL)
	{
		//printf("remove :%s\n", content);
		free(content);
	}
	content = NULL;
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
		head = NULL; // inutil
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

void	ms_lst_free_all(t_list_envp *head)
{
	while (head->next != NULL)
		ms_lst_pop_end(head);
	remove_lst_content(head->content);
	free(head);
	head = NULL; // inutil
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

t_list_envp	*ms_lst_point(int index, t_list_envp *ms_env)
{
	t_list_envp	*tmp;

	tmp = ms_env;
	if (index <= 0)
		return (ms_env);
	while (index-- > 0)
		tmp = tmp->next;
	return (tmp);
}

void	ms_lst_pop_inside(t_list_envp *current, t_list_envp *prev)
{
	t_list_envp *tmp;

	if (!current)
		return ;
	if (!prev)
		return ;
	if (current == prev)
		return ;
	tmp = current;
	prev->next = current->next;
	remove_lst_content(tmp->content);
	free(tmp);
}
