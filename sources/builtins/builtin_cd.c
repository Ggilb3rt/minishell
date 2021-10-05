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

need to interpret ~ and -
~ = $HOME
- = $OLDPWD ; working, need parsing to see if I must free(path)

- print pwd
*/

char	*select_path_dash_op(char *path, t_list_envp *ms_env)
{
	if (!path)
		return (NULL);
	if (path[0] == '-')
	{
		if (ms_strlen(path) > 1)
		{
			if (path[1] != ' ')
			{
				return (path);
			}
		}
		//free(path);
		path = get_ms_env_val("OLDPWD", ms_env);
	}
	return (path);
}

char	*update_ms_env_value(char *new_val, int	ms_index, t_list_envp *ms_env)
{
	// free ms_env[index]->content
	// ms_env[index]->content = strdup new_val
	int			i;
	t_list_envp	*tmp;

	i = 0;
	tmp = ms_env;
	printf("start update val tmp %p\n", tmp);
	while (i++ < ms_index)
		tmp = tmp->next;
	free(tmp->content);
	tmp->content = ms_strdup(new_val);
	printf("strdup res %p | %s\n", tmp, tmp->content);
	return (tmp->content);
}

char	*update_pwds(t_list_envp *ms_env, char **env)
{
	t_list_envp	*tmp;
	char		*pwd;

	tmp = ms_env;
	printf("start update pwd tmp %p\n", tmp);
	pwd = get_env_val("PWD", env);
	pwd = update_ms_env_value(pwd, get_ms_env_index("PWD", ms_env), tmp);
	// free env[PWD]->content
	// env[PWD]->content = strdup(env[PWD])

	// free env[OLDPWD]->content
	// env[OLDPWD]->content = strdup(env[OLDPWD])
	return (pwd);
}

/*
dont use path because must free (with path maybe need free)

! need to update pwd and oldpwd
*/
int	cmd_cd(char *path, t_list_envp *ms_env, char **env)
{
	int		err;
	char	*msg;
	//char	*next_old_path;

	msg = NULL;
	//next_old_path = get_ms_env_val("PWD", ms_env);
	path = select_path_dash_op(path, ms_env);
	err = chdir(path);
	if (err == -1)
	{
		msg = ms_strjoin("cd: ", path);
		perror(msg);
		free(msg);
		return (1);
	}
	//next_old_path = update_pwds(ms_env, env);
	printf("USE OF THE CD COMMAND : %s\nNEWPWD %s\n", path,
			get_env_val("PWD", env));
	return (0);
}
