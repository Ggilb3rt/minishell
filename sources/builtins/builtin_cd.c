//
// Created by Antoine LANGLOIS on 22/09/2021.
//

#include "minishell.h"

/* cd with only a relative or absolute path
 * - cd shall change the working directory of the current shell execution environment
 * if relative we can go in the desired directory by typing the path from the actual directory
 * if absolute we can go in the desired directory by typing the path from the root.
 * If, during the execution of the above steps, the 'PWD' environment variable is set, the 'OLDPWD' environment
 * variable shall also be set to the value of the old working directory (that is the current working directory
 * immediately prior to the call to 'cd').
 */

/* external functions that we may use :
 * - int chdir(const char *path) : changes the current working directory of the calling process to the directory
 * specified in path.
 */

/*
return 0 if ok, 1 otherwise (permission denied, No such file or directory)

need to interpret ~ and - (not true)
~ = $HOME
- = $OLDPWD ; working, need parsing to see if I must free(path)

- print pwd
*/

char	*select_path_dash_op(char *path, t_list_envp *ms_env)
{
	if (!path)
		return (get_ms_env_val(HOME, ms_env));
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
		path = get_ms_env_val(OLDPWD, ms_env);
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
dont use path because must free (with path maybe need free)
*/

int	cmd_cd(char *path, t_list_envp *ms_env)
{
	int		err;
	char	*msg;

	msg = NULL;
	path = select_path_dash_op(path, ms_env);
	err = chdir(path);
	if (err == -1)
	{
		msg = ft_strjoin("cd: ", path);
		perror(msg);
		free(msg);
		return (1);
	}
	update_old_pwd(ms_env);
	cmd_pwd(ms_env, 0);
	return (0);
}
