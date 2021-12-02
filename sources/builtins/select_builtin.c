/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 08:13:19 by ggilbert          #+#    #+#             */
/*   Updated: 2021/12/02 08:18:31 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(char **cmd, t_list_envp *env, int print)
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
		return (cmd_export(env, cmd, print));
	else if (!strcmp(cmd_name, "unset"))
		return (cmd_unset(&env, cmd));
	else if (!strcmp(cmd_name, "env"))
		return (cmd_env(env));
	else if (!strcmp(cmd_name, "exit"))
		return (cmd_exit(cmd));
	return (0);
}

void	set_builtin(char *cmd_name, t_command *cur)
{
	if (!strcmp(cmd_name, "echo"))
		cur->build = BUILT_ECHO;
	else if (!strcmp(cmd_name, "cd"))
		cur->build = BUILT_CD;
	else if (!strcmp(cmd_name, "pwd"))
		cur->build = BUILT_PWD;
	else if (!strcmp(cmd_name, "export"))
		cur->build = BUILT_EXPORT;
	else if (!strcmp(cmd_name, "unset"))
		cur->build = BUILT_UNSET;
	else if (!strcmp(cmd_name, "env"))
		cur->build = BUILT_ENV;
	else if (!strcmp(cmd_name, "exit"))
		cur->build = BUILT_EXIT;
	else
		cur->build = -1;
}
