/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 11:49:59 by ggilbert          #+#    #+#             */
/*   Updated: 2021/12/02 12:50:39 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* cd with only a relative or absolute path
 * - cd shall change the working directory of the current shell execution
 * environment if relative we can go in the desired directory by typing
 * the path from the actual directory if absolute we can go in the desired 
 * directory by typing the path from the root.
 * If, during the execution of the above steps, the 'PWD' environment variable
 * is set, the 'OLDPWD' environment variable shall also be set to the value 
 * of the old working directory (that is the current working directory
 * immediately prior to the call to 'cd').
 */

/* external functions that we may use :
 * - int chdir(const char *path) : changes the current working directory of 
 * the calling process to the directory specified in path.
 */

/*
return 0 if ok, 1 otherwise (permission denied, No such file or directory)

need to interpret ~ and -
~ = $HOME ; working
- = $OLDPWD ; working, need parsing to see if I must free(path)

- print pwd
*/

char	*change_tild(char *path, t_list_envp *env)
{
	if (path == NULL || path[0] == '\0')
		return (ft_strdup(get_ms_env_val(HOME, env)));
	if (path[0] == '~')
		return (ft_strjoin(get_ms_env_val(HOME, env), path + 1));
	return (ft_strdup(path));
}

char	*select_path_dash_op(char *path, t_list_envp *ms_env)
{
	if (!path)
		return (ft_strdup(get_ms_env_val(HOME, ms_env)));
	if (get_ms_env_index(OLDPWD, ms_env) == -1)
		return (path);
	if (path[0] == '-')
	{
		if (ft_strlen(path) > 1)
		{
			if (path[1] != ' ')
				return (path);
		}
		free(path);
		path = ft_strdup(get_ms_env_val(OLDPWD, ms_env));
	}
	return (path);
}

void	update_old_pwd(t_list_envp *env)
{
	char		*current_pwd;
	int			index_old_pwd;
	char		*next_old_pwd;
	t_list_envp	*tmp;

	tmp = env;
	index_old_pwd = get_ms_env_index(OLDPWD, tmp);
	if (index_old_pwd == -1)
		return ;
	current_pwd = get_ms_env_val(PWD, tmp);
	next_old_pwd = ft_strjoin(OLDPWD, current_pwd);
	edit_lst_content(tmp, index_old_pwd, next_old_pwd);
	free(next_old_pwd);
}

/*
cd segfault if use multiple times
==> because **path dont have null at the end when change path[1] (null) by path[1] ($HOME)
*/

int	cmd_cd(char **path, t_list_envp *ms_env)
{
	int		err;
	char	*msg;
	char	*new_path;

	msg = NULL;
	if (array_size(path) > 2)
	{
		printf("minishell: cd: too many arguments\n");
		return (g_ret.ret = 1);
	}
	new_path = change_tild(path[1], ms_env);
	new_path= select_path_dash_op(new_path, ms_env);
	err = chdir(new_path);
	free(new_path);
	if (err == -1)
	{
		msg = ft_strjoin("minishell: cd: ", path[1]);
		perror(msg);
		free(msg);
		return (g_ret.ret = 1);
	}
	update_old_pwd(ms_env);
	cmd_pwd(ms_env, 0);
	return (0);
}
