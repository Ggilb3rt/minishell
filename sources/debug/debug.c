//
// Created by Antoine LANGLOIS on 27/09/2021.
//

#include "minishell.h"
/*
int	print_command(t_command **cmd)
{
	printf("out file = %s\n", cur_c->out_file);
	printf("in file = %s\n", cur_c->in_file);
	printf("err file = %s\n", cur_c->err_file);
	return (0);
}
*/
int	print_simple_command(t_command **c)
{
	t_command			*cur_c;
	t_simple_command	*cur;
	int					i;
	int					j;
	int					count;
	int					arr_size;

	j = 0;
	cur_c = *c;
	while (cur_c != NULL)
	{
		arr_size = 0;
		count = 0;
		cur = (*cur_c->list);
		printf("COMMAND TABLE %d:\n", j);
		while (cur != NULL)
		{
			i = 0;
			arr_size = array_size(cur->arg) + 1;
			while (i < arr_size) {
				printf("%i %s = %i\n", count, cur->arg[i], cur->token);
				i++;
			}
			cur = cur->next;
			count++;
		}
		printf("out file = %s\n", cur_c->out_file);
		printf("in file = %s\n", cur_c->in_file);
		printf("err file = %s\n", cur_c->err_file);
		j++;
		cur_c = cur_c->next;
	}
	return (0);
}
