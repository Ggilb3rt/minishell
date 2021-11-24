//
// Created by Antoine LANGLOIS on 27/09/2021.
//

#include "minishell.h"

int	print_command(t_command *cmd)
{
	printf("out file = %s\n", cmd->out_file);
	printf("in file = %s\n", cmd->in_file);
	printf("err file = %s\n", cmd->err_file);
	return (0);
}

int	print_all(t_command **cmd)
{
	char				**arr;
	int					i;
	int					count;

	count = 0;
	printf("COMMAND TABLE :\n");
	while ((*cmd) != NULL)
	{
		i = 0;
		arr = (*cmd)->arg;
		while (arr[i])
		{
			printf("%i %s\n", count, arr[i]);//, (*cmd)->token);
			i++;
		}
		print_command(*cmd);
		printf("\n");
		(*cmd) = (*cmd)->next;
		count++;
	}

	/*
	int j = 0;
	t_command *cur;

	cur = *cmd;
	while (cur != NULL)
	{
		for (int i = 0; cur->arg[i] != NULL; i++)
		{
			printf("%d %d stparg = %s\n", j, i, cur->arg[i]);
		}
		cur = cur->next;
		j++;
	}
	 */
	return (0);
}
