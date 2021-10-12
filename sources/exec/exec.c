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

// some trouble with free (I don't change anything, it's works on 42's Mac...)
char	**convert_envplst_to_tab(t_list_envp *ms_env)
{
	char	**tmp_env;
	size_t	len_ms_env;
	size_t	i;

	len_ms_env = get_ms_env_len(ms_env);
	tmp_env = malloc(sizeof(char *) + (len_ms_env + 1));
	if (!tmp_env)
		return (NULL);
	printf("malloc %p\n", tmp_env);
	i = 0;
	while (i < len_ms_env)
	{
		tmp_env[i] = ms_env->content;
		ms_env = ms_env->next;
		i++;
	}
	tmp_env[i] = NULL;
	return (tmp_env);
}
