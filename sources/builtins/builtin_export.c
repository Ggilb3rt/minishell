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
int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	else
		return (0);
}

char	*ms_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s != (char)c)
			s++;
		else
			return ((char *)s);
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (0);
}





int	check_valide_identifier(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0' || arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]))
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

// char *arg must be change by char ** after (remove split and free_tab)
int	cmd_export(t_list_envp *env, char *arg)
{
	char	**args;
	int		i;
	int		has_err;
	int		equal_pos;
	char	*identifier;

	args = ms_split(arg, ' ');
	if (args == NULL)
		return (0);
	i = 0;
	has_err = 0;
	while (args[i] != NULL)
	{
		equal_pos = check_valide_identifier(args[i]);
		if (equal_pos > 0)
		{
			identifier = get_identifier(args[i], equal_pos);
			if (!identifier)
				return (0);
			if (get_ms_env_index(identifier, env) != -1)
				edit_lst_content(env, get_ms_env_index(identifier, env), args[i]);
			else
				ms_lst_push_end(&env, new_char_list(args[i]));
			free(identifier);
		}
		else
		{
			printf("export: not valid in this context: %s\n", args[i]);
			has_err = 1;
		}
		i++;
	}
	free_tab(args);
	return (has_err);
}
