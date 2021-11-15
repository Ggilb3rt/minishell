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

int	print_simple_command(t_simple_command **cur)
{
	char 				**arr;
	int					i;
	int					count;

	count = 0;
	printf("COMMAND TABLE :\n");
	while ((*cur) != NULL)
	{
		i = 0;
		arr = (*cur)->arg;
		while (arr[i])
		{
			printf("%i %s = %i\n", count, arr[i], (*cur)->token);
			i++;
		}
		(*cur) = (*cur)->next;
		count++;
	}
	return (0);
}

int	print_all(t_command **cmd)
{
	t_command	*cur;

	cur = *cmd;
	while (cur != NULL)
	{
		printf("---cur---\n");
		print_simple_command(cur->list);
		print_command(cur);
		printf("\n");
		cur = cur->next;
	}
	return (0);
}
