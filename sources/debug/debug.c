//
// Created by Antoine LANGLOIS on 27/09/2021.
//

#include "minishell.h"

int print_simple_command(t_simple_command **sc)
{
	t_simple_command	*cur;
	int					i;
	int 				count;
	int 				arr_size;

	arr_size = 0;
	count = 0;
	cur = *sc;
	while (cur->next != NULL)
	{
		i = 0;
		arr_size = array_size(cur->arg);
		while (i < arr_size)
		{
			printf("arg[%i] = %s, token[%i] = %s\n", count, cur->arg[i], count, cur->token[i]);
			i++;
		}
		cur = cur->next;
		count++;
	}
	/*
	i = 0;
	arr_size = array_size(cur->arg);
	while (i < arr_size)
	{
		printf("arg[%i] = %s, token[%i] = %s\n", count, cur->arg[i], count, cur->token[i]);
		i++;
	}
	 */
	return (0);
}