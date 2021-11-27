/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 15:03:00 by alangloi          #+#    #+#             */
/*   Updated: 2021/11/27 17:57:45 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// priorities pipe (|) then redirect (< > >> <<) then others

//! NEW VERSION

void	exec_built_or_bin(t_command *cur, char **env, t_list_envp *lst)
{
	int ret;


	if (cur->build >= 0)
	{
		if (cur->build >= 10)
			exit(0);
		ret = exec_builtin(cur->arg, lst);
		//free_all();
		exit(ret);
	}
	else if (execve(cur->arg[0], cur->arg, env) == -1)
	{
		g_ret.ret = errno;
		perror(cur->arg[0]);
		// close(pipe_fd[0][0]);
		// close(pipe_fd[0][1]);
		// close(pipe_fd[1][0]);
		// close(pipe_fd[1][1]);
		exit(errno);
	}
	//fprintf(stderr, "just before exec |%s| |%s|\n", cur->arg[0], cur->arg[1]);
	g_ret.ret = execve(cur->arg[0], cur->arg, env);
	//fprintf(stderr, "errore ??\n");
	perror(cur->arg[0]);
	exit(errno);
}
