/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 11:12:42 by ggilbert          #+#    #+#             */
/*   Updated: 2021/11/24 12:09:44 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_read_access(char *path, int *fd)
{
	if (access(path, F_OK | R_OK) == -1)
	{
		*fd = -2;
		perror(path);
		return (0);
	}
	*fd = open(path, O_RDONLY);
	if (*fd == -1)
	{
		perror(path);
		return (0);
	}
	return (1);
}

int	open_out_file(int cur_token, char *path, int *fd_out)
{
	printf("open out file : %d\n", cur_token);
	if (cur_token == GREAT)
		*fd_out = open(path, O_CREAT | O_WRONLY | O_CLOEXEC, 0666);
	else if (cur_token == DGREAT)
		*fd_out = open(path, O_CREAT | O_WRONLY | O_APPEND | O_CLOEXEC, 0666);
	if (*fd_out == -1 && (cur_token == GREAT || cur_token == DGREAT))
	{
		perror(path);
		return (-1);
	}
	return (0);
}

int	init_files_fds(int cur_token, char *path, int *fd_in, int *fd_out)
{
	if (cur_token == LESS)
	{
		if (!check_read_access(path, fd_in))
			return (-1);
	}
	//else if (cur_token == DLESS)
	//	*fd_in = 1;
	else if (cur_token == GREAT)
		*fd_out = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	else if (cur_token == DGREAT)
		*fd_out = open(path, O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (*fd_out == -1 && (cur_token == GREAT || cur_token == DGREAT))
	{
		perror(path);
		return (errno);
	}
	return (0);
}

int	associate_file_to_cmd(t_command *cmds)
{
	t_simple_command	*cur;
	int					current_token;

	cur = cmds->list[0];
	while (cur != NULL)
	{
		current_token = cur->token;
		if (current_token == GREAT || current_token == DGREAT
			|| current_token == LESS || current_token == DLESS)
		{
			if (init_files_fds(current_token, cur->arg[1],
					&cmds->fd_in, &cmds->fd_out) < 0)
				return (-1);
		}
		cur = cur->next;
	}
	return (0);
}

void	set_builtin(char *cmd_name, t_command *cur)
{
	if (!strcmp(cmd_name, "echo"))
		cur->list[0]->build = BUILT_ECHO;
	else if (!strcmp(cmd_name, "cd"))
		cur->list[0]->build = BUILT_CD;
	else if (!strcmp(cmd_name, "pwd"))
		cur->list[0]->build = BUILT_PWD;
	else if (!strcmp(cmd_name, "export"))
		cur->list[0]->build = BUILT_EXPORT;
	else if (!strcmp(cmd_name, "unset"))
		cur->list[0]->build = BUILT_UNSET;
	else if (!strcmp(cmd_name, "env"))
		cur->list[0]->build = BUILT_ENV;
	else if (!strcmp(cmd_name, "exit"))
		cur->list[0]->build = BUILT_EXIT;
	else
		cur->list[0]->build = -1;
}

int	set_cmd_ready_to_exec(t_command **cmd, t_list_envp *env)
{
	t_command	*cur;
	int			ret_file;
	char		*env_path;

	cur = *cmd;
	while (cur != NULL)
	{
		ret_file = associate_file_to_cmd(cur);
		if (ret_file < 0)
			return (ret_file);
		set_builtin(cur->list[0]->arg[0], cur);
		if (cur->list[0]->token != NWLINE)
		{
			env_path = get_ms_env_val(PATH, env);
			if (cur->list[0]->build == -1)
				cur->list[0]->arg[0] = init_cmd_path(cur->list[0]->arg[0],
						env_path);
		}
		if (access(cur->list[0]->arg[0], X_OK) == -1)
			cur->can_exec = 0;
			// perror(cur->list[0]->arg[0]);
		else
			cur->can_exec = 1;
		cur = cur->next;
	}
	return (0);
}
