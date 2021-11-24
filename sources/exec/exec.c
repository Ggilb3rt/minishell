/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 15:03:00 by alangloi          #+#    #+#             */
/*   Updated: 2021/11/24 12:08:25 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// priorities pipe (|) then redirect (< > >> <<) then others

void	parent_exec(t_command *cur, char **env, int *fd, t_list_envp *lst)
{
	close(fd[0]);
	if (cur->fd_out != -1)
	{
		dup2(cur->fd_out, STDOUT_FILENO);
		close(cur->fd_out);
	}
	else
		dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	if (cur->list[0]->build >= 0)
	{
		if (cur->list[0]->build >= 10)
			exit(0);
		exit(exec_builtin(cur->list[0]->arg, lst));
	}
	else if (execve(cur->list[0]->arg[0], cur->list[0]->arg, env) == -1)
	{
		perror(cur->list[0]->arg[0]);
		close(fd[0]);
		close(fd[1]);
		exit(errno);
	}
}

int	multiple_cmds(t_command *cur, char **env, int fd[2], t_list_envp *lst)
{
	pid_t		pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (errno);
	}
	else if (pid > 0)
		process_pipe(fd, cur->fd_in);
	else
		parent_exec(cur, env, fd, lst);
	return (0);
}

void	one_cmd(t_command *cur, char **env, t_list_envp *env_lst)
{
	if (cur->fd_out != -1)
	{
		dup2(cur->fd_out, STDOUT_FILENO);
		close(cur->fd_out);
	}
	if (cur->fd_in != -1)
	{
		dup2(cur->fd_in, STDIN_FILENO);
		close(cur->fd_in);
	}
	if (cur->list[0]->build >= 0)
	{
		if (cur->list[0]->build >= 10)
			exit(0);
		exit(exec_builtin(cur->list[0]->arg, env_lst));
	}
	else if (execve(cur->list[0]->arg[0], cur->list[0]->arg, env) == -1)
	{
		perror(cur->list[0]->arg[0]);
		exit(errno);
	}
}

int	execute_pipeline_cmds(t_command **cmd, char **env, int fd[2], t_list_envp *lst)
{
	t_command	*cur;

	cur = *cmd;
	if (!cur)
		return (-1);
	while (cur != NULL && cur->list[0]->token != NWLINE)
	{
		//printf("fd_in %d, fd_out %d, %s : %d\n", cur->fd_in, cur->fd_out, cur->list[0]->arg[0], cur->can_exec);
		//if (cur->can_exec == 1)
		//{
			if (cur->next != NULL && cur->next->list[0]->token != NWLINE)
			{
				if (multiple_cmds(cur, env, fd, lst) != 0)
					return (-1);
			}
			else
				one_cmd(cur, env, lst);
		//}
		//else
		// {
		// 	close(fd[0]);
		// 	close(fd[1]);
		// 	printf("error cmd\n");
		// }
		cur = cur->next;
	}
	return (0);
}

int	ms_pipeline(t_command **cmd, char **env, t_list_envp *lst)
{
	int		fd[2];
	pid_t	global_pid;
	pid_t	ret_exec;
	int		exit_code;

	ret_exec = -1;
	ms_pipe(fd);
	if (cmd[0]->list[0]->build >= 10)
		exec_builtin(cmd[0]->list[0]->arg, lst);
	global_pid = fork();
	if (global_pid == -1)
	{
		perror("global fork");
		return (errno);
	}
	else if (global_pid == 0)
		ret_exec = execute_pipeline_cmds(cmd, env, fd, lst);
	else if (global_pid > 0)
	{
		close(fd[0]);
		close(fd[1]);
		waitpid(global_pid, &exit_code, 0);
	}
	return (ret_exec);
}
