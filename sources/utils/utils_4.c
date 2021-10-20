//
// Created by Antoine LANGLOIS on 23/09/2021.
//

#include "minishell.h"

void 	free_tab(char **arr)
{
	int i;

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
/*
void	free_command(t_command *cmd)
{
	while (cmd->list != NULL)
	{
		free_simple_command(cmd->list);
		free(cmd->list);
		cmd->list = NULL;
		cmd->list = cmd->list->next;
	}
}

void 	free_simple_command(t_simple_command **list)
{
	int 				i;
	int 				size;

	while (list != NULL)
	{
		size = array_size(list->arg);
		i = 0;
		while (i < size)
		{
			free(cur->arg[i]);
			cur->arg[i] = NULL;
			i++;
		}
		free(cur->arg);
		cur->arg = NULL;
		list = list->next;
	}
}
 */