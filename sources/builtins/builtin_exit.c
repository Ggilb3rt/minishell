/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 11:45:07 by ggilbert          #+#    #+#             */
/*   Updated: 2021/12/02 17:56:31 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* exit with no options : exit 'n'
 * - cause the shell to exit from its current execution environment with the
 * exit status specified by the unsigned decimal integer 'n'. If the current
 * execution environment is a subshell environment, the shell
 * shall exit from the subshell environment with the specified exit status
 * and continue in the environment from which that subshell environment was
 * invoked; otherwise, the shell utility shall terminate with
 * the specified exit status. If 'n' is specified, but its
 * value is not between 0 and 255 inclusively, the exit status is undefined
 */

/* the exit command should interrupt the prompt if "exit" is typen 
 * or if CTRL-D is pressed in the case if CTRL-D is pressed,
 * refer to a specific function stored with the other functions
 * involving key pressed (CTRL-C, CTRL-\)
 */

/*
* Exemples de tests
*
* bash> exit				==> 0
* bash> exit 42				==> 42
* bash> exit 256			==> 0
* bash> exit -42			==> 214
* 
* bash> exit | exit			==> do nothing + return 0
* bash> exit 42 | exit -42	==> do nothing + return 214
* 
* bash> exit a				==> exit + err numeric arg required + return 255
* bash> exit a 42			==> exit + err numeric arg required + return 255
* bash> exit a a			==> == exit a 42
* bash> exit 28374623874627346234629423423 ==> == exit a 42
* 
* bash> exit 42 a			==> no exit + err too many arg + return 1
* 
* MAX value supported is long long : 9223372036854775807
* 
* ret de exit est toujours entre 0 et 255 ==> convertir en unsigned char
*/

int	ft_can_int_convert(char *arg)
{
	int		atoi_res;
	char	*itoa_res;

	atoi_res = ft_atoi(arg);
	itoa_res = ft_itoa(atoi_res);
	if (ft_strcmp(itoa_res, arg) == 0)
	{
		free(itoa_res);
		return (1);
	}
	free(itoa_res);
	return (0);
}

int	has_one_arg(char **args, t_command *cur, int print)
{
	if (args[2] == NULL)
	{
		g_ret.ret = (unsigned char)ft_atoi(args[1]);
		if (cur->next != NULL && cur->next->token != NWLINE && cur->nb_cmd >= 1)
			g_ret.quit = 0;
		else
			g_ret.quit = 1;
		if (print)
			printf("exit\n");
		return (1);
	}
	return (0);
}

void	set_quit(t_command *cur)
{
	if (cur->next != NULL && cur->next->token != NWLINE && cur->nb_cmd >= 1)
		g_ret.quit = 0;
	else
		g_ret.quit = 1;
}

int	cmd_exit(char **args, t_command *cur, int print)
{
	if (!args)
		return (0);
	if (ft_strcmp(args[0], "exit") == 0)
	{
		set_quit(cur);
		if (args[1] == NULL)
		{
			if (print)
				printf("exit\n");
			return (0);
		}
		if (ft_isnbr(args[1]))
		{
			if (ft_can_int_convert(args[1]))
			{
				if (has_one_arg(args, cur, print))
					return (g_ret.ret);
				else
					return (too_many_arg_err(print));
			}
		}
		return (not_numeric_arg_err(args[1], print));
	}
	return (0);
}
