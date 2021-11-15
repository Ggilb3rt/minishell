//
// Created by antoine on 15/11/2021.
//

#include "minishell.h"

void convert_var(t_command **cmd)
{
	t_command *cur;
	t_simple_command *tmp;
	int i;
	int j;
	int k;
	char *str;
	char *var;

	cur = *cmd;
	while (cur)// && cur->next)
	{
		tmp = (*cur->list);
		while (tmp)// && tmp->next)
		{
			i = 0;
			while (tmp->arg[i])
			{
				j = 0;
				str = tmp->arg[i];
				while (str[j])
				{
					printf("\t%c\n", str[j]);
					if (str[j] == '$')
					{
						printf("test\n");
						k = 0;
						var = NULL;
						printf("j = %i\n", j);
						while (str[j + k] != ' ' || str[j + k])
							k++;
						printf("k = %i\n", k);
						var = ft_substr(str, j, k);
						if (var)
						{
							printf("var = %s\n", var);
							j += k;
						}
					}
					j++;
				}
				i++;
			}
			tmp = tmp->next;
		}
		cur = cur->next;
	}
}
