/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 15:03:00 by alangloi          #+#    #+#             */
/*   Updated: 2021/11/27 17:41:02 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// priorities pipe (|) then redirect (< > >> <<) then others

//! NEW VERSION

void	exec_built_or_bin(t_command *cur, char **env, t_list_envp *lst)
{
	if (cur->list[0]->build >= 0)
	{
		if (cur->list[0]->build >= 10)
			exit(0);
		exit(exec_builtin(cur->list[0]->arg, lst));
	}
	else if (execve(cur->list[0]->arg[0], cur->list[0]->arg, env) == -1)
	{
		g_ret.ret = errno;
		perror(cur->list[0]->arg[0]);
		// close(pipe_fd[0][0]);
		// close(pipe_fd[0][1]);
		// close(pipe_fd[1][0]);
		// close(pipe_fd[1][1]);
		exit(errno);
	}
}
