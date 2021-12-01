/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alangloi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 14:33:42 by alangloi          #+#    #+#             */
/*   Updated: 2021/11/26 14:33:44 by alangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_cmd(t_command ***cmd)
{
	*cmd = malloc(sizeof(t_command *));
	if (!*cmd)
		return (0);
	**cmd = NULL;
	return (1);
}

void	init_split(t_split *split, char *str)
{
	(void)str;
	split->str = str;
	split->i = 0;
	split->l = 0;
	split->o = 0;
	split->q = 0;
	split->new = NULL;
	split->red = 0;
	split->open_s = 0;
	split->open_d = 0;
}

int	init_arg(t_split *split, t_list_envp *ms_env, t_command **cur)
{
	*cur = alloc_command(NULL);
	//printf("create cmd\t%p\n", *cur);
	if (!*cur)
		return (0);
	split->o = 0;
	split->l = 0;
	if (!alloc_arg(split))
		return (0);
	if (!alloc_word(split, ms_env))
		return (0);
	return (1);
}
