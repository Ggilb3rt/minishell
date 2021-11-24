/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 11:55:08 by ggilbert          #+#    #+#             */
/*   Updated: 2021/11/24 11:55:33 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* env with no options or arguments : env 'NAME'='value'
 * - run a program in a modified environment. Set each 'NAME' to 'value'
 * in the environment.
 * Working only with the current call, NAME become her origin value 
 * after end of env
 *
 * if var exist change her value
 * if !var create new and put it to the end
 * print env
 
 * I need to create a tmp env ? and share it with others if pipe ?
 * env PWD=pouet | pwd			==> /Users/login/xx/xx (env don't affect pwd)
 * env NAME=pouet | echo $NAME	==> \n (env don't affect echo)
 */

/*t_ms_envp	init_ms_envp(char **env)
{
	t_ms_envp	new;

	(void)new;
	return (new);
}*/

int	cmd_env(t_list_envp *ms_envp)
{
	print_envp(ms_envp, 0);
	return (0);
}
