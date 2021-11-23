//
// Created by Antoine LANGLOIS on 22/09/2021.
//

#include "minishell.h"

/* exit with no options : exit 'n'
 * - cause the shell to exit from its current execution environment with the exit status specified by the
 * unsigned decimal integer 'n'. If the current execution environment is a subshell environment, the shell
 * shall exit from the subshell environment with the specified exit status and continue in the environment from
 * which that subshell environment was invoked;
 * otherwise, the shell utility shall terminate with the specified exit status. If 'n' is specified, but its
 * value is not between 0 and 255 inclusively, the exit status is undefined
 */

/* the exit command should interrupt the prompt if "exit" is typen or if CTRL-D is pressed
 * in the case if CTRL-D is pressed, refer to a specific function stored with the other functions
 * involving key pressed (CTRL-C, CTRL-\)
 */


/*
Exemples de tests

bash> exit				==> 0
bash> exit 42			==> 42
bash> exit 256			==> 0
bash> exit -42			==> 214

bash> exit | exit		==> do nothing + return 0
bash> exit 42 | exit -42	==> do nothing + return 214

bash> exit a			==> exit + err numeric arg required + return 255
bash> exit a 42			==> exit + err numeric arg required + return 255
bash> exit a a			==> == exit a 42
bash> exit 28374623874627346234629423423 ==> == exit a 42

bash> exit 42 a			==> no exit + err too many arg + return 1

MAX value supported is long long : 9223372036854775807

le retour de exit est toujour compris entre 0 et 255 ==> convertir en unsigned char
*/

int	ft_nbr_smaller_ll(char *arg)
{
	long	nb;
	char	**endpoint;

	endpoint = malloc(sizeof(char *));
	endpoint[0] = &arg[ft_strlen(arg) - 1];
	printf("endpoitn %p |%s|\n", endpoint[0], endpoint[0]);
	nb = strtol(arg, endpoint, 10);
	printf("NB %ld, %p, %p\n", nb, arg, endpoint[0]);
	if (endpoint[0] == arg)
		return (1);
	return (1);
}

int	too_many_arg_err(void)
{
	g_ret.ret = 1;
	g_ret.quit = 0;
	printf("minishell: exit: too many arguments\n");
	return (1);
}

int	not_numeric_arg_err(char *arg)
{
	g_ret.ret = 255;
	g_ret.quit = 1;
	printf("minishell : exit : %s: numeric argument required\n", arg);
	return (255);
}

int	ft_isnbr(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) || str[0] == '-')
			i++;
		else
			return (0);
	}
	return (1);
}

int	cmd_exit(char **args)
{
	long	nb;

	g_ret.ret = 0;
	if (!args)
		return (0);
	if (ft_strcmp(args[0], "exit") == 0)
	{
		if (args[1] == NULL)
		{
			g_ret.quit = 1;
			g_ret.ret = 0;
			printf("exit\n");
			return (0);
		}
		if (ft_isnbr(args[1]))
		{
			if (ft_nbr_smaller_ll(args[1]))
			{
				if (args[2] == NULL)
				{
					nb = strtol(args[1], NULL, 10);
					g_ret.ret = (unsigned char)nb;
					g_ret.quit = 1;
					printf("exit\n");
					return ((unsigned char)nb);
				}
				else
					return (too_many_arg_err());
			}
		}
		return (not_numeric_arg_err(args[1]));
	}
	return (0);
}
