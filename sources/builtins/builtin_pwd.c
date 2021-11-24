/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 12:01:24 by ggilbert          #+#    #+#             */
/*   Updated: 2021/11/24 12:02:35 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* pwd with no options
 * - print the full filename of the current working directory
 */

/* external function that we may use :
 * - char *getcwd(char *buf, size_t size) : this function return a 
 * null-terminated string containing an absolute pathname that is the current
 * working directory of the calling process. The pathname is returned
 * as the function result and via the argument 'buf', which is of length 'size'.
 * If the length of the absolute pathname of the current working directory,
 * including the terminating null byte, exceeds 'size' bytes, NULL is returned,
 * and 'errno' is set the ERANGE; an application should check for this error,
 * and allocate a larger buffer if necessary.
 * The function allocates the buffer dynamically using 'malloc' if 'buf' is NULL.
 * In this case, the allocated buffer hat the length 'size' unless 'size'
 * is zero, when 'buf' is allocated as big as necessary. The caller should
 * 'free' the returned buffer.
 */

int	cmd_pwd(t_list_envp *env, int print)
{
	char	*buf;
	char	*new_pdw;

	buf = NULL;
	buf = getcwd(buf, 0);
	if (!buf)
	{
		perror("getcwd() error");
		return (errno);
	}
	new_pdw = ft_strjoin(PWD, buf);
	edit_lst_content(env, get_ms_env_index(PWD, env), new_pdw);
	if (print)
		printf("%s\n", buf);
	free(new_pdw);
	free(buf);
	return (0);
}
