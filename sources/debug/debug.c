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
	printf("COMMAND TABLE :\n");
	while (cur != NULL)
	{
		i = 0;
		arr_size = array_size(cur->arg) + 1;
		while (i < arr_size)
		{
			printf("%i %s = %s \n", count, cur->arg[i], cur->token[i]);
			i++;
		}
		cur = cur->next;
		count++;
	}
	return (0);
}