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
	dup2(fd[1], 1);
	fprintf(stderr, "fd duped %d %d\n", *fd, *(fd + 1));
	close(fd[0]);
	close(fd[1]);
	execve((*cmd)[0], *cmd, env);
}

void	child_exec(int *fd)
{
	static int i = 0;

	fprintf(stderr, "execute child %d | %d %d\n", i++, *fd, *(fd + 1));
	dup2(fd[0], 0);
	fprintf(stderr, "fd duped %d %d\n", *fd, *(fd + 1));
	close(fd[1]);
	close(fd[0]);
	ms_pipe(fd);
}

// ! pipeline working well, some trouble when cat -e at the end (no it's probably cat /dev/urandom)
int	pipeline(char ***cmd, char **env)
{
	int	fd[2];
	int	pid;

	ms_pipe(fd);
	while (*cmd != NULL)
	{
		if (*(cmd + 1) != NULL)
		{
			pid = fork();
			if (pid == -1)
			{
				perror("fork");
				exit(errno);
			}
			else if (pid > 0)
				parent_exec(cmd, env, fd);
			else
				child_exec(fd);
		}
		else
		{
			//pid = fork();
			//if (pid == 0)
				execve((*cmd)[0], *cmd, env);
		}
		cmd++;
	}
	return (pid);
}


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
