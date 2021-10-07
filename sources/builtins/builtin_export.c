//
// Created by Antoine LANGLOIS on 22/09/2021.
//

#include "minishell.h"

/* export with no options : export 'name'='word'
 * - Set export attribute for shell variables, corresponding to the specified 'name', which shall cause them to
 * be in the environment of subsequently executed builtins. If the name of a variable is followed by ='word', then
 * the value of that variable shall be set to 'word'.
 * The shell shall format the ouptut, including the proper use of quoting, so that it is suitable for reinput to the
 * shell as builtins that achieve the same exporting results.
 */

/* things we need to know :
 * ' inhibit all interpretation of a sequence of characters.
 * " inhibit all interpretation of a sequence of characters except for $.
 */

/*
export POUET=pouet	==> add to end of list (on mac not at the end but before last, need to check on linux)
export LEL=lel LOL=lol ==> add each item
export POO=foo POUET=nooon ==> add POO and update POUET
export	(void) ==> print list of exported var (pas besoin de le gerer a priori car pas defini dans le man general)

*before '=' must be alphanum

split the list of items
foreach item check if exist
	if exist ==> update
	if !exist ==> create
*/

int	check_valide_identifier(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0' || arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			break ;
		i++;
	}
	if (arg[i] != '=')
		return (0);
	return (i);
}

char	*get_identifier(char *arg, int equal_pos)
{
	char	*identifier;
	int		i;

	i = 0;
	identifier = malloc(sizeof(char) * (equal_pos + 2));
	if (!identifier)
		return (NULL);
	while (i <= equal_pos)
	{
		identifier[i] = arg[i];
		i++;
	}
	identifier[i] = '\0';
	return (identifier);
}

int	export_update_env(t_list_envp *env, int equal_pos, char *arg)
{
	char	*identifier;

	identifier = get_identifier(arg, equal_pos);
	if (!identifier)
		return (0);
	if (get_ms_env_index(identifier, env) != -1)
		edit_lst_content(env, get_ms_env_index(identifier, env),
			arg);
	else
		ms_lst_push_end(&env, new_char_list(arg));
	free(identifier);
	return (1);
}

int	cmd_export(t_list_envp *env, char **args)
{
	int		i;
	int		has_err;
	int		equal_pos;

	if (args == NULL)
		return (0);
	i = -1;
	has_err = 0;
	while (args[++i] != NULL)
	{
		equal_pos = check_valide_identifier(args[i]);
		if (equal_pos > 0)
		{
			if (!export_update_env(env, equal_pos, args[i]))
				return (0);
		}
		else
		{
			printf("minishell: export: not valid in this context: %s\n",
				args[i]);
			has_err = 1;
		}
	}
	return (has_err);
}
