/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 15:03:00 by alangloi          #+#    #+#             */
/*   Updated: 2021/11/24 20:31:29 by ggilbert         ###   ########.fr       */
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
	if (cur->build >= 0)
	{
		if (cur->build >= 10)
			exit(0);
		exit(exec_builtin(cur->arg, lst));
	}
	else if (execve(cur->arg[0], cur->arg, env) == -1)
	{
		fprintf(stderr, "parent error ??\n");
		perror(cur->arg[0]);
		close(fd[0]);
		close(fd[1]);
		exit(errno);
	}
}

int	multiple_cmds(t_command *cur, char **env, int fd[2], t_list_envp *lst)
{
	pid_t		pid;

	//printf("multiple cmd\n");

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
	//fprintf(stderr, "build %d\n", cur->build);
	if (cur->build >= 0)
	{
		if (cur->build >= 10)
			exit(0);
		exit(exec_builtin(cur->arg, env_lst));
	}
	//fprintf(stderr, "just before exec |%s| |%s|\n", cur->arg[0], cur->arg[1]);
	execve(cur->arg[0], cur->arg, env);
	fprintf(stderr, "errore ??\n");
	perror(cur->arg[0]);
	exit(errno);
}

int	execute_pipeline_cmds(t_command **cmd, char **env, int fd[2], t_list_envp *lst)
{
	t_command	*cur;

	cur = *cmd;
	//printf("exc %s %d %d %s\n", cur->arg[0], cur->fd_out, cur->fd_in, cur->out_file);
	if (!cur)
		return (-1);
	while (cur != NULL && cur->token != NWLINE)
	{
		//printf("fd_in %d, fd_out %d, %s : %d\n", cur->fd_in, cur->fd_out, cur->list[0]->arg[0], cur->can_exec);
		//if (cur->can_exec == 1)
		//{
			if (cur->next != NULL && cur->next->token != NWLINE)
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

	t_command *cur = cmd[0];
	(void)cur;
	//printf("pipeline %s %d %d %s\n", cur->arg[0], cur->fd_out, cur->fd_in, cur->out_file);
	ret_exec = -1;
	ms_pipe(fd);
	if (cmd[0]->build >= 10)
		exec_builtin(cmd[0]->arg, lst);
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
