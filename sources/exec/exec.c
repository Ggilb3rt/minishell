/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 15:03:00 by alangloi          #+#    #+#             */
/*   Updated: 2021/11/19 18:59:49 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//
// Created by Antoine LANGLOIS on 23/09/2021.
//

#include "minishell.h"

/* external functions that we may use :
 * - int execve(const char *pathname, char *const argv[], char *const envp[]) : executes the program referred to by
 * pathname. This causes the program that is currently being run by the calling process to be replaced with a new
 * program, with newly initialized stack, heap, and (initialized and uninitialized) data segments.
 * 'pathname' must be either a binary executable, or a script starting with a line of the form :
 * 		#!interpetrer (in our case /bin/sh)
 * 'argv' is an array of pointers to strings passed to the new program as its command-line arguments. By convention,
 * the first of these strings should contain the filename associated with the file being executed. The 'argv' array
 * must be terminted by a NULL pointer.
 * 'envp' is an arry of pointers to strings, conventionally of the form key=value, which are passed as the
 * environment of the new program. The 'envp' array must be terminated by a NULL pointer.
 * The argument vector and environment can be accessed by the new program's main function, when it is defined as:
 * 		int main(int argc, char *argv[], char *envp[])
 *
 * - pid_t fork(void) : creates a new process by duplicating the calling process. The new process is referred
 * to as the 'child' process. The calling process is referred to as the 'parent' process.
 * The child process and the parent process run in separate memory spaces. At the time of 'fork()' both memory spaces
 * have the same content. Memory writes performed by one of the process do not affect the other.
 * The child process is an exact duplicate of the parent process except for the following points:
 * - The child has its own unique process ID, and this PID does not match the ID of any existing process group or
 * session.
 * - The child's parent process ID is the same as the parent's process ID.
 */

// priorities pipe (|) then redirect (< > >> <<) then others

void	ms_pipe(int *fd)
{
	if (pipe(fd) != 0)
	{
		perror("pipe");
		exit(errno);
	}
}

void	process_pipe(int *fd, int fd_in)
{
	close(fd[1]);
	if (fd_in != -1)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	else
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
	ms_pipe(fd);
}

void	parent_exec(char **list, char **env, int *fd, int fd_out)
{
	// Parent execute cmd and send output to child
	//static int i = 0;

	//fprintf(stderr, "execute parent %d | %d %d\n", i++, *fd, *(fd + 1));
	close(fd[0]);
	if (fd_out != -1)
	{
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	else
		dup2(fd[1], STDOUT_FILENO);
	//fprintf(stderr, "fd duped %d %d\n", *fd, *(fd + 1));
	close(fd[1]);
	if (execve(list[0], list, env) == -1)
	{
		perror(list[0]);
		close(fd[0]);
		close(fd[1]);
		exit(errno);
	}
}

int	multiple_cmds(t_command *cur, char **env, int fd[2])
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
		parent_exec(cur->list[0]->arg, env, fd, cur->fd_out);
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
		exit(exec_builtin(cur->list[0]->arg, env_lst));
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
				if (multiple_cmds(cur, env, fd) != 0)
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
	pid_t	parent_ret;
	int		exit_code;

	ret_exec = -1;
	ms_pipe(fd);
	printf("pointeur sur %p pipeline\n", lst);
	if (cmd[0]->list[0]->build >= 0)
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
		parent_ret = waitpid(global_pid, &exit_code, 0);
		//printf("hi end %d | %d\n", parent_ret, exit_code);
	}
	//printf("return exec %d\n", ret_exec);
	return (ret_exec);
}
