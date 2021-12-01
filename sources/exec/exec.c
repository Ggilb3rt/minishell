/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 15:03:00 by alangloi          #+#    #+#             */
/*   Updated: 2021/12/01 17:03:10 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// priorities pipe (|) then redirect (< > >> <<) then others

void	set_g_ret_err(t_command *cur)
{
	perror(cur->arg[0]);
	g_ret.ret = 127;
	g_ret.quit = 1;
}

int	exec_built_or_bin(t_command *cur, char **env, t_list_envp *lst)
{
	if (cur->arg[0] == NULL)
	{
		g_ret.ret = 2;
		exit(2);
	}
	if (cur->build >= 0)
	{
		if (cur->build >= 10)
		{
			g_ret.quit = 1;
			return (-1);
		}
		exec_builtin(cur->arg, lst);
		g_ret.quit = 1;
		return (-1);
	}
	else if (execve(cur->arg[0], cur->arg, env) == -1)
	{
		set_g_ret_err(cur);
		return (-1);
	}
	set_g_ret_err(cur);
	return (-1);
}
