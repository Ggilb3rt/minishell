/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alangloi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 17:36:49 by alangloi          #+#    #+#             */
/*   Updated: 2021/11/29 17:36:51 by alangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_command(t_command *cmd)
{
	printf("out file = %s\n", cmd->out_file);
	printf("in file = %s\n", cmd->in_file);
	printf("here file = %s\n", cmd->end);
	printf("nb_cmd = %d\n", cmd->nb_cmd);
	return (0);
}

int	print_all(t_command **cmd)
{
	char				**arr;
	int					i;
	int					count;
	t_command			*cur;

	cur = *cmd;
	count = 0;
	printf("COMMAND TABLE :\n");
	while (cur != NULL)
	{
		i = 0;
		arr = cur->arg;
		while (arr[i])
		{
			printf("[%i] [%s]\n", count, arr[i]);
			i++;
		}
		printf("[%i] [%s]\n", count, arr[i]);
		print_command(cur);
		printf("\n");
		cur = cur->next;
		count++;
	}
	return (0);
}
