/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 17:33:30 by ggilbert          #+#    #+#             */
/*   Updated: 2021/12/02 08:28:00 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	connect_inside(pid_t pid, t_command *cur, int *old, int *new)
{
	if (pid == 0)
	{
		if (cur->nb_cmd > 1)
		{
			dup2(old[0], 0);
			close(old[0]);
			close(old[1]);
		}
		if (cur->next != NULL && cur->next->token != NWLINE)
		{
			close(new[0]);
			dup2(new[1], 1);
			close(new[1]);
		}
	}
	else
	{
		if (cur->nb_cmd > 1)
			close_pipe(old);
		if (cur->next != NULL && cur->next->token != NWLINE)
		{
			old[0] = new[0];
			old[1] = new[1];
		}
	}
}

int	set_exec_pipeline(t_command *cur, t_pipes *p, char **env, t_list_envp *lst)
{
	pid_t	pid;

	while (cur != NULL && cur->token != NWLINE)
	{
		if (cur->next != NULL && cur->next->token != NWLINE)
			if (ms_pipe(p->new_pipe) != 0)
				return (-1);
		pid = fork();
		ms_signal(2);
		if (pid == -1)
		{
			perror("can't fork");
			return (-1);
		}
		else if (pid == 0)
		{
			connect_inside(pid, cur, p->old_pipe, p->new_pipe);
			if (!set_redir(cur, p->new_pipe))
				return (-1);
			if (exec_built_or_bin(cur, env, lst) == -1)
				return (-1);
		}
		connect_inside(pid, cur, p->old_pipe, p->new_pipe);
		cur = cur->next;
	}
	return (0);
}

int	ms_pipeline(t_command **cmd, char **env, t_list_envp *lst)
{
	t_command	*cur;
	t_pipes		pipes;

	cur = *cmd;
	if (cmd[0]->build >= 10)
		exec_builtin(cmd[0]->arg, lst, 0);
	if (set_exec_pipeline(cur, &pipes, env, lst) != 0)
		return (-1);
	waiter();
	if (cur->nb_cmd > 1)
	{
		close(pipes.old_pipe[0]);
		close(pipes.old_pipe[1]);
	}
	return (0);
}

/*
Pseudo-code

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
