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
		printf("%s\n", content);
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

t_list_envp	*create_msenvp_lst(char **envp)
{
	t_list_envp	*ms_envp;
	int	i;

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
