/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 15:03:00 by alangloi          #+#    #+#             */
/*   Updated: 2021/11/28 19:05:31 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// priorities pipe (|) then redirect (< > >> <<) then others

//! NEW VERSION

void	exec_built_or_bin(t_command *cur, char **env, t_list_envp *lst, t_command **cmd)
{
	int	ret;

	if (cur->arg[0] == NULL)
	{
		g_ret.ret = 2;
		exit(2);
	}
	if (cur->build >= 0)
	{
		if (cur->build >= 10)
		{
			free_all(cmd);
			exit(0);
		}
		ret = exec_builtin(cur->arg, lst);
		exit(ret);
	}
	else if (execve(cur->arg[0], cur->arg, env) == -1)
	{
		g_ret.ret = errno;
		perror(cur->arg[0]);
		exit(errno);
	}
	//fprintf(stderr, "just before exec |%s| |%s|\n", cur->arg[0], cur->arg[1]);
	perror(cur->arg[0]);
	exit(errno);
}
