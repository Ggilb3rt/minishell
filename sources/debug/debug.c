//
// Created by Antoine LANGLOIS on 27/09/2021.
//

#include "minishell.h"

int print_simple_command(t_simple_command *sc)
{
	t_simple_command	*cur;
	int					i;
	int 				arr_size;

	arr_size = 0;
	cur = sc;
	while (cur->next != NULL)
	{
		i = 0;
		arr_size = array_size(cur->arg);
		while (i < arr_size)
		{
			printf("arg = %s\n", cur->arg[i]);
			i++;
		}
		cur = cur->next;
	}
	return (0);
}