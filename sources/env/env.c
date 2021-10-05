//
// Created by Antoine LANGLOIS on 24/09/2021.
//

#include "minishell.h"

void	print_envp(t_list_envp *head)
{
	t_list_envp	*current;

	current = head;
	while (current != NULL)
	{
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
	head->content = ms_strdup(str);
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
	ms_envp = new_char_list(envp[i]);
	i++;
	while (envp[i] != NULL)
	{
		ms_lst_push_end(&ms_envp, new_char_list(envp[i]));
		i++;
	}
	return (ms_envp);
}
