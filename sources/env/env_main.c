/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 11:56:08 by ggilbert          #+#    #+#             */
/*   Updated: 2021/11/28 20:22:02 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_envp(t_list_envp *head, int export)
{
	t_list_envp	*current;

	current = head;
	while (current != NULL)
	{
		if (export)
			printf("declare -x %s\n", current->content);
		else
			printf("%s\n", current->content);
		current = current->next;
	}
}

t_list_envp	*new_char_list(char *str)
{
	t_list_envp	*head;

	head = malloc(sizeof(t_list_envp));
	if (!head)
		return (NULL);
	head->content = ft_strdup(str);
	if (head->content == NULL)
	{
		free(head);
		return (NULL);
	}
	head->next = NULL;
	return (head);
}

t_list_envp	*create_msenvp_lst(char **envp)
{
	t_list_envp	*ms_envp;
	int			i;

	i = 0;
	if (envp[0] == NULL)
	{
		printf("Pas de variable d'environnements.\nJe rentre a ma maison.\n");
		exit(-1);
	}
	ms_envp = new_char_list(envp[i]);
	i++;
	while (envp[i] != NULL)
	{
		ms_lst_push_end(&ms_envp, new_char_list(envp[i]));
		i++;
	}
	return (ms_envp);
}
