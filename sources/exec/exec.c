/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 15:03:00 by alangloi          #+#    #+#             */
/*   Updated: 2021/11/26 11:23:28 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// priorities pipe (|) then redirect (< > >> <<) then others

void	parent_exec(t_command *cur, char **env, int *fd, t_list_envp *lst)
{
	printf("starting parent %s fd %d %d %d %d\n", cur->list[0]->arg[0],
		fd[0], fd[1], cur->fd_in, cur->fd_out);
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
		printf("builtins parent fd %d %d %d %d\n",
			fd[0], fd[1], cur->fd_in, cur->fd_out);
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

/* ! Pourquoi j'avais inverse process_pipe et parent_exec ?
 * cat | cat | ls fonctionne bien quand process_pipe est dans
 * le child (pid == 0) mais avec une pipe trop longue ca merde
 * 	==> reponse : ca merde pas, c'est juste que la boucle recommence
 * 				  il faut mieux gerer le wait
 * 
 * si process_pipe est dans le parent (pid > 0) cat | cat | ls merde
 * mais une pipe tres longue fonctionne...
 * 
 * il est plus logique que le parent execute process_pipe car c'est lui
 * qui doit gerer les pipes et le child execute le program
*/
int	multiple_cmds(t_command *cur, char **env, int fd[2], t_list_envp *lst)
{
	pid_t		pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (errno);
	}
	else if (pid == 0)
	{
		process_pipe(fd, cur->fd_in);
	//else
		parent_exec(cur, env, fd, lst);
	}
	printf("multiple cmd end\n");
	return (0);
}

int	one_cmd(t_command *cur, char **env, t_list_envp *env_lst, int fd[2])
{
	printf("starting onecmd %s\n", cur->list[0]->arg[0]);
	close(fd[0]);
	close(fd[1]);
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
		g_ret.ret = errno;
		exit(errno);
	}
	return (0);
}

int	execute_pipeline_cmds(t_command **cmd, char **env, int fd[2], t_list_envp *lst)
{
	t_command	*cur;
	int			ret;

	cur = *cmd;
	ret = 0;
	if (!cur)
		return (-1);
	while (cur != NULL && cur->list[0]->token != NWLINE)
	{
		//printf("fd_in %d, fd_out %d, %s : %d\n", cur->fd_in, cur->fd_out, cur->list[0]->arg[0], cur->can_exec);
		//if (cur->can_exec == 1)
		//{
			if (cur->next != NULL && cur->next->list[0]->token != NWLINE)
			{
				
				ret = multiple_cmds(cur, env, fd, lst);
				if (ret != 0)
					return (-1);
			}
			else
				ret = one_cmd(cur, env, lst, fd);
		//}
		//else
		// {
		// 	close(fd[0]);
		// 	close(fd[1]);
		// 	printf("error cmd\n");
		// }
		printf("end pipeline %d\n", cur->next->list[0]->token);
		cur = cur->next;
	}
	printf("fucking NWLINE %d\n", cur->list[0]->token);
	return (ret);
}

// int	ms_pipeline(t_command **cmd, char **env, t_list_envp *lst)
// {
// 	int		fd[2];
// 	pid_t	global_pid;
// 	pid_t	ret_exec;
// 	int		exit_code = 0;

// 	ret_exec = 18;
// 	ms_pipe(fd);
// 	if (cmd[0]->list[0]->build >= 10)
// 		exec_builtin(cmd[0]->list[0]->arg, lst);
// 	global_pid = fork();
// 	if (global_pid == -1)
// 	{
// 		perror("global fork");
// 		return (errno);
// 	}
// 	else if (global_pid == 0)
// 	{
// 		ret_exec = execute_pipeline_cmds(cmd, env, fd, lst);
// 		close(fd[0]);
// 		close(fd[1]);
// 	}
// 	else if (global_pid > 0)
// 	{
// 		close(fd[0]);
// 		close(fd[1]);
// 		waitpid(global_pid, &exit_code, 0);
// 		printf("end waitpid %d %d\n", exit_code, ret_exec);
// 	}
// 	return (ret_exec);
// }
void	exec_built_or_bin(t_command *cur, char **env, t_list_envp *lst)
{
	if (cur->list[0]->build >= 0)
	{
		printf("builtins fd %d %d %d %d\n",
			*cur->pipe_out, *cur->pipe_in, cur->fd_in, cur->fd_out);
		if (cur->list[0]->build >= 10)
			exit(0);
		exit(exec_builtin(cur->list[0]->arg, lst));
	}
	else if (execve(cur->list[0]->arg[0], cur->list[0]->arg, env) == -1)
	{
		perror(cur->list[0]->arg[0]);
		//close(fd[0]);
		//close(fd[1]);
		exit(errno);
	}
}

int		create_pipes(t_command **cmd)
{
	t_command	*cur;
	int			*pipefd;

	cur = *cmd;
	while (cur != NULL && cur->list[0]->token != NWLINE)
	{
		pipefd = malloc(sizeof(int) * 2);
		if (!pipefd)
			return (-1);
		if (pipe(pipefd) != 0)
		{
			perror("Can't create pipe");
			return (-2);
		}
		cur->pipe_in = &pipefd[0];
		cur->pipe_out = &pipefd[1];
		printf("pipefd %d %d\n", pipefd[0], pipefd[1]);
		printf("write %d>=====>%d read\n", *cur->pipe_in, *cur->pipe_out);
		cur = cur->next;
	}
	return (0);
}

void	free_pipes(t_command **cmd)
{
	t_command	*cur;

	cur = *cmd;
	while (cur != NULL && cur->list[0]->token != NWLINE)
	{
		close(*cur->pipe_out);
		close(*cur->pipe_in);
		free(cur->pipe_in);
		cur->pipe_in = NULL;
		cur->pipe_out = NULL;
		cur = cur->next;
	}

}

void	set_pipes(t_command *cur, int nb_cmd)
{
	if (nb_cmd == 0)
	{
		close(*cur->pipe_in);
		close(*cur->pipe_out);
		if (cur->next->list[0]->token == NWLINE || cur->next == NULL)
		{
			printf("just one cmd\n");
			return ;
		}
		else
		{
			printf("first cmd\n");
			dup2(*cur->next->pipe_in, STDOUT_FILENO);
			close(*cur->next->pipe_in);
			// read from STDIN_FILENO
			// write to cur->pipe_out
		}
	}
	if (nb_cmd > 0)
	{
		if (cur->next->list[0]->token == NWLINE || cur->next == NULL)
		{
			printf("last cmd %d\n", *cur->pipe_in);
			close(*cur->pipe_out);
			dup2(*cur->pipe_in, STDIN_FILENO);
			printf("%d\n", *cur->pipe_in);
			close(*cur->pipe_in);
			printf("%d\n", *cur->pipe_in);
			// read from pipe_prec out
			// write to STDOUT_FILENO
		}
		else
		{
			printf("cmd %d\n", nb_cmd);
			// read from pipe_prec out
			// write to cur->pipe_out
		}
	}
}

int	ms_pipeline(t_command **cmd, char **env, t_list_envp *lst)
{
	t_command	*cur;
	pid_t		pid;
	int			status;
	//int			pipe[2];
	int			nb_cmd;

	//ms_pipe(pipe);
	nb_cmd = 0;
	create_pipes(cmd);
	printf("table size = %d\n", getdtablesize());
	if (cmd[0]->list[0]->build >= 10)
		exec_builtin(cmd[0]->list[0]->arg, lst);
	cur = *cmd;
	while(cur != NULL && cur->list[0]->token != NWLINE)
	{
		printf("cur %s\n", cur->list[0]->arg[0]);
		pid = fork();
		if (pid == -1)
		{
			perror("can't fork");
			return (-1);
		}
		else if (pid == 0)
		{
			//pipe
			set_pipes(cur, nb_cmd);
			//process_pipe(pipe, cur->fd_in);
			//redirect
			//exec
			exec_built_or_bin(cur, env, lst);
			//execve(cur->list[0]->arg[0], cur->list[0]->arg, env);
			perror("execve");
			exit(-1);
		}
		cur = cur->next;
		nb_cmd++;
	}
	while (wait(&status) > 0)
			printf("waiting...");
	if (g_ret.ret == -1 || status == 0)
		g_ret.ret = (unsigned char)status;
	free_pipes(cmd);
	//close(pipe[0]);
	//close(pipe[1]);
	return (0);
}


/*

while (cmd)
	fork()
	if (error)
		manage error
	else if (child)
		manage redirection
		manage pipe
		execute cmd
	else (parent)
		wait()
	next_cmd

*/