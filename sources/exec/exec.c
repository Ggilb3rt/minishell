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

/*
fork
	perror

	waitpid

	execve
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

void	parent_exec(char ***cmd, char **env, int *fd)
{
	// Parent execute cmd and send output to child
	static int i = 0;

	fprintf(stderr, "execute parent %d | %d %d\n", i++, *fd, *(fd + 1));
	//close(1);
	dup2(fd[1], 1);
	fprintf(stderr, "fd duped %d %d\n", *fd, *(fd + 1));
	close(fd[1]);
	close(fd[0]);
	execve((*cmd)[0], *cmd, env);
}

void	child_exec(int *fd)
{
	static int i = 0;

	fprintf(stderr, "execute child %d | %d %d\n", i++, *fd, *(fd + 1));
	//close(0);
	dup2(fd[0], 0);
	fprintf(stderr, "fd duped %d %d\n", *fd, *(fd + 1));
	close(fd[0]);
	close(fd[1]);
	ms_pipe(fd);
}

// ! pipeline working well, some trouble when cat -e at the end (no it's probably cat /dev/urandom)
int	pipeline2(char ***cmd, char **env)
{
	int		fd[2];
	pid_t	pid;

	ms_pipe(fd);
	while (*cmd != NULL)
	{
		if (*(cmd + 1) != NULL)
		{
			pid = fork();
			if (pid == -1)
			{
				perror("fork");
				return (errno);
			}
			else if (pid > 0)
			{
				parent_exec(cmd, env, fd);
				//wait(NULL);
			}
			else
				child_exec(fd);
		}
		else // last cmd
		{
			//pid = fork();
			//if (pid == 0)
				execve((*cmd)[0], *cmd, env);
			//else if (pid > 0)
			//	wait(NULL);
		}
		cmd++;
	}
	return (0);
}

int	pipeline(char ***cmd, char **env)
{
	int		fd[2];
	pid_t	*pid;
	int		i;
	int		nb_cmd = 4; // replace i
	pid_t	global_pid;
	int		status;

	i = 0;
	status = 0;
	pid = malloc(sizeof(pid_t) * nb_cmd);
	ms_pipe(fd);
	global_pid = fork();
	printf("\n\nglobal1 %d\n\n", global_pid);
	if (global_pid == -1)
	{
		perror("global fork");
		return (errno);
	}
	else if (global_pid == 0)
	{
		while (*cmd != NULL)
		{
			printf("\tcmd[%d]\n", i);
			if (*(cmd + 1) != NULL)
			{
				pid[i] = fork();
				if (pid[i] == -1)
				{
					perror("fork");
					exit(errno);
				}
				else if (pid[i] > 0)
					parent_exec(cmd, env, fd);
				else
				{
					child_exec(fd);
				}
			}
			else
			{
				//pid[i] = fork();
				//if (pid[i] == 0)
					execve((*cmd)[0], *cmd, env);
			}
			cmd++;
			i++;
		}
		while (i-- > 0)
		{
			printf("waitiiiiing\n");
			//pid_t childpid = waitpid(pid[i], NULL, 0);
			//printf("childpid %d\n", childpid);
		}
		return (0);
	}
	else if (global_pid > 0)
	{
		printf("global_pid %d\n", global_pid);
		//waitpid(global_pid, &status, 0);
		wait(&status);
		printf("after parent wait\n");
	}
	printf("qui es tu ? %d\n", status);
	return (0);
}


void	new_pipeline(t_command **cmds)
{
	int					fd[2];
	//int				pid;
	int					i;
	t_simple_command	*cur;

	ms_pipe(fd);
	i = 0;
	while (i < 1) // while (cmds[i] != NULL)
	{
		printf("i in %d\n", i);
		cur = cmds[i]->list[0];
		while (cur != NULL)
		{
			// while to get each arg (but no need for pipeline)
			printf("cmd %d %s\nin %s\nout %s\n\n", i, cur->arg[0],
				cmds[i]->in_file, cmds[i]->out_file);
			if (!ms_strcmp(cmds[i]->in_file, "dflt"))
			{
				/*
				dup2(fd[0], cmds[i]->in_file);
				close(fd[0]);
				close[fd[1]];
				*/
			}
			if (!ms_strcmp(cmds[i]->out_file, "dflt"))
			{
				/*
				dup2(fd[1], cmds[i]->out_file);
				close(fd[0]);
				close[fd[1]];
				*/
			}
			cur = cur->next;
		}
		i++;
	}
}
/*
 * loop over commands by sharing
 * pipes.
 */
/*
void	pipeline2(char ***cmd, char **env)
{
	int		fd[2];
	pid_t	pid;
	int		fdd;

	fdd = 0; //Backup
	while (*cmd != NULL)
	{
		if (pipe(fd) == -1)
		{
			perror("pipe");
			exit(1);
		}
		pid = fork();
		if (pid == -1)
		{
			close(fd[0]);
			close(fd[1]);
			perror("fork");
			exit(1);
		}
		else if (pid == 0)
		{
			dup2(fdd, 0);
			if (*(cmd + 1) != NULL)
				dup2(fd[1], 1);
			close(fd[0]);
			if (execve((*cmd)[0], *cmd, env) == -1)
				perror("execve");
			exit(1);
		}
		else
		{
			waitpid(pid, NULL, 0);
			close(fd[1]);
			fdd = fd[0];
			cmd++;
		}
	}
}
*/
/*
void	put_err(char *str)
{
	write(STDERR_FILENO, str, ms_strlen(str));
}

void	close_unneeded(unsigned int *c, int *from, int *to)
{
	if (*c == UINT_MAX)
		*c = 2;
	if (*c % 2 == 1)
	{
		close(from[0]);
		close(from[1]);
		close(to[0]);
	}
	else
	{
		close(to[0]);
		close(to[1]);
		close(from[1]);
	}
}

pid_t	exec_from_to(int from[2], int to[2], char **cmd, char **envp)
{
	pid_t				pid;
	static unsigned int	count = 1;

	pid = fork();
	if (pid == 0)
	{
		dup2(from[0], STDIN_FILENO);
		dup2(to[1], STDOUT_FILENO);
		close_unneeded(&count, from, to);
		count++;
		execve(cmd[0], cmd, envp);
		if (errno == 2)
		{
			put_err(cmd[0]);
			put_err(": command not found\n");
			exit(EXIT_FAILURE);
		}
		else
		{
			perror(cmd[0]);
			exit(EXIT_FAILURE);
		}
	}
	return (pid);
}
*/

// some troubles with free ; I don't change anything, it's works on 42's Mac... ;
// troubles with free came from forks (maybe ?)
char	**convert_envplst_to_tab(t_list_envp *ms_env)
{
	char	**tmp_env;
	size_t	len_ms_env;
	size_t	i;

	len_ms_env = get_ms_env_len(ms_env);
	tmp_env = malloc(sizeof(char *) + (len_ms_env + 1));
	if (!tmp_env)
		return (NULL);
	i = 0;
	while (i < len_ms_env)
	{
		tmp_env[i] = ms_strdup(ms_env->content);
		ms_env = ms_env->next;
		i++;
	}
	tmp_env[i] = NULL;
	return (tmp_env);
}
