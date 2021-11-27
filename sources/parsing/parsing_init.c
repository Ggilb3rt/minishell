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

void	init_split(t_split *split, char *str)
{
	(void)str;
	split->str = str;
	split->i = 0;
	split->l = 0;
	split->o = 0;
	split->q = 0;
	split->open_s = 0;
	split->open_d = 0;
}

int	init_arg(t_split *split, t_list_envp *ms_env, t_command **cur)
{
	//printf("init arg\n");
	*cur = alloc_command(NULL);
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
