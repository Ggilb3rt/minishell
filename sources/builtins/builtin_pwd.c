//
// Created by Antoine LANGLOIS on 22/09/2021.
//

#include "minishell.h"

/* pwd with no options
 * - print the full filename of the current working directory
 */

/* external function that we may use :
 * - char *getcwd(char *buf, size_t size) : this function return a null-terminated string containing an
 * absolute pathname that is the current working directory of the calling process. The pathname is returned
 * as the function result and via the argument 'buf', which is of length 'size'.
 * If the length of the absolute pathname of the current working directory, including the terminating null byte,
 * exceeds 'size' bytes, NULL is returned, and 'errno' is set the ERANGE; an application should check for this error,
 * and allocate a larger buffer if necessary.
 * The function allocates the buffer dynamically using 'malloc' if 'buf' is NULL. In this case, the allocated buffer
 * hat the length 'size' unless 'size' is zero, when 'buf' is allocated as big as necessary. The caller should
 * 'free' the returned buffer.
 */

// ! need to print in the good fd, do I need to manage it here or with pipe ?

/* return int or char * ?
	nothing in the man (linux)
	when echo $? after pwd got 0 in bash
*/

int	cmd_pwd(char *ms_pwd, int print)
{
	char	*buf;

	buf = NULL;
	buf = getcwd(buf, 0);
	if (!buf)
	{
		perror("BUILTIN PWD ERROR");
		return (errno);
	}
	printf("before %s | %p\n", ms_pwd, ms_pwd);
	free(ms_pwd);
	printf("freed %p\n", ms_pwd);
	ms_pwd = ms_strdup("poeut");
	printf("after %s | %p\n", ms_pwd, ms_pwd);
	if (print)
		printf("%s\n", buf);
	free(buf);
	return (0);
}
