//
// Created by Antoine LANGLOIS on 28/09/2021.
//

#include "minishell.h"

static void	*list_last(t_simple_command *list)
{
	if (!list)
		return (NULL);
	while (list->next != NULL)
		list = list->next;
	return (list);
}

void 	insert_command(t_simple_command *new, t_simple_command **list_arg) {
	t_simple_command *cur;

	if (!new)
		return;
	if (!*list_arg) {
		new->next = *list_arg;
		*list_arg = new;
	}
	else
	{
		cur = list_last(*list_arg);
		cur->next = new;
		cur->next->next = NULL;
	}
}

t_simple_command	*alloc_command(char **str)
{
	t_simple_command *new;

	if (!str)
		return (NULL);
	new = malloc(sizeof(t_simple_command));
	if (!new)
		return (NULL);
	new->arg = str;
	new->numb_avail++;
	new->numb++;
	new->next = NULL;
	return (new);
}