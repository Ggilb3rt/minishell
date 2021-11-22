/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 08:13:19 by ggilbert          #+#    #+#             */
/*   Updated: 2021/11/22 08:13:39 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(char **cmd, t_list_envp *env)
{
	char	*cmd_name;

	if (!cmd || !cmd[0])
		return (0);
	cmd_name = cmd[0];
	if (!strcmp(cmd_name, "echo"))
		return (cmd_echo(cmd));
	else if (!strcmp(cmd_name, "cd"))
		return (cmd_cd(cmd[1], env));
	else if (!strcmp(cmd_name, "pwd"))
		return (cmd_pwd(env, 1));
	else if (!strcmp(cmd_name, "export"))
		return (cmd_export(env, cmd));
	else if (!strcmp(cmd_name, "unset"))
		return (cmd_unset(&env, cmd));
	else if (!strcmp(cmd_name, "env"))
		return (cmd_env(env));
	else if (!strcmp(cmd_name, "exit"))
		return (cmd_exit(cmd_name));
	return (0);
}