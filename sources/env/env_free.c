/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 08:43:21 by ggilbert          #+#    #+#             */
/*   Updated: 2021/10/08 08:44:16 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_lst_content(char *content)
{
	if (content != NULL)
		free(content);
	content = NULL;
}

void	ms_lst_free_all(t_list_envp *head)
{
	if (!head)
		return ;
	while (head->next != NULL)
		ms_lst_pop_end(head);
	remove_lst_content(head->content);
	free(head);
	head = NULL;
}
