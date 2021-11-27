/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 15:03:00 by alangloi          #+#    #+#             */
/*   Updated: 2021/11/27 16:46:00 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// priorities pipe (|) then redirect (< > >> <<) then others

//! NEW VERSION

void	exec_built_or_bin(t_command *cur, char **env, t_list_envp *lst)
{
	// fprintf(stderr, "execution fd %d %d %d %d\n",
	// 	pipe_fd[0][0], pipe_fd[0][1], cur->fd_in, cur->fd_out);
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

void	set_redir(t_command *cur, int pipe_fd[2])
{
	if (cur->fd_in != -1)
	{
		close(pipe_fd[1]);
		dup2(cur->fd_in, STDIN_FILENO);
		close(cur->fd_in);
	}
	if (cur->fd_out != -1)
	{
		close(pipe_fd[0]);
		dup2(cur->fd_out, STDOUT_FILENO);
		close(cur->fd_out);
	}
}

void	set_pipes(t_command *cur, int nb_cmd, int old_pipe[2], int new_pipe[2])
{
	(void)cur;
	(void)nb_cmd;
	(void)old_pipe;
	(void)new_pipe;
}

void	waiter(void)
{
	int	status;

	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			g_ret.ret = WEXITSTATUS(status);
	}
	if (g_ret.ret == -1 || status == 0)
		g_ret.ret = (unsigned char)status;
}

int	ms_pipeline(t_command **cmd, char **env, t_list_envp *lst)
{
	t_command	*cur;
	int			old_pipe[2];
	int			new_pipe[2];
	pid_t		pid;
	int			nb_cmd;

	cur = *cmd;
	nb_cmd = 0;
	if (cmd[0]->list[0]->build >= 10)
		exec_builtin(cmd[0]->list[0]->arg, lst);
	while (cur != NULL && cur->list[0]->token != NWLINE)
	{
		if (cur->next != NULL && cur->next->list[0]->token != NWLINE)
		{
			if (ms_pipe(new_pipe) != 0)
				return (-1);
		}
		pid = fork();
		if (pid == -1)
		{
			perror("can't fork");
			return (-1);
		}
		else if (pid == 0)
		{
			if (nb_cmd > 0) // if prev cmd
			{
				dup2(old_pipe[0], 0);
				close(old_pipe[0]);
				close(old_pipe[1]);
			}
			if (cur->next != NULL && cur->next->list[0]->token != NWLINE) // if next cmd
			{
				close(new_pipe[0]);
				dup2(new_pipe[1], 1);
				close(new_pipe[1]);
			}
			exec_built_or_bin(cur, env, lst);
		}
		else
		{
			if (nb_cmd > 0)
			{
				close(old_pipe[0]);
				close(old_pipe[1]);
			}
			if (cur->next != NULL && cur->next->list[0]->token != NWLINE) // if next cmd
			{
				old_pipe[0] = new_pipe[0];
				old_pipe[1] = new_pipe[1];
			}
		}
		nb_cmd++;
		cur = cur->next;
	}
	waiter();
	// while (wait(&status) > 0)
	// {
	// 	if (WIFEXITED(status))
	// 		g_ret.ret = WEXITSTATUS(status);
	// }
	// if (g_ret.ret == -1 || status == 0)
	// 	g_ret.ret = (unsigned char)status;
	if (nb_cmd > 1)
	{
		close(old_pipe[0]);
		close(old_pipe[1]);
	}
	return (0);
}

/*

for cmd in cmds
    if there is a next cmd
        pipe(new_fds)
    fork
    if child
        if there is a previous cmd
            dup2(old_fds[0], 0)
            close(old_fds[0])
            close(old_fds[1])
        if there is a next cmd
            close(new_fds[0])
            dup2(new_fds[1], 1)
            close(new_fds[1])
        exec cmd || die
    else
        if there is a previous cmd
            close(old_fds[0])
            close(old_fds[1])
        if there is a next cmd
            old_fds = new_fds
if there are multiple cmds
    close(old_fds[0])
    close(old_fds[1])

*/