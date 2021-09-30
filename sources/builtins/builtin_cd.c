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

char	*get_old_path(char *path, char **env)
{
	int		len;
	int		env_old_pwd;

	if (!path)
		return (NULL);
	len = 0;
	env_old_pwd = 0;
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
		path = get_env_val("OLDPWD", env);
	}
	return (path);
}

/*
dont use path because must free (with path maybe need free)
*/
int	cmd_cd(char *path, char **env)
{
	int		err;
	char	*msg;

	msg = NULL;
	path = get_old_path(path, env);
	err = chdir(path);
	if (err == -1)
	{
		msg = ms_strjoin("cd: ", path);
		perror(msg);
		free(msg);
		return (1);
	}
	printf("USE OF THE CD COMMAND : %s\n", path);
	return (0);
}
