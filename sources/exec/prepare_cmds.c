/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 11:12:42 by ggilbert          #+#    #+#             */
/*   Updated: 2021/11/28 21:30:42 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	associate_file_to_cmd(t_command *cmds)
{
	t_command	*cur;
	int			current_token;

	cur = cmds;
	current_token = cur->token_out;
	if (current_token == GREAT || current_token == DGREAT)
	{
		if (init_out_file_fd(current_token, cur->out_file,
				&cmds->fd_out) < 0)
			return (-1);
	}
	current_token = cur->token_in;
	if (current_token == LESS || current_token == DLESS)
	{
		if (init_in_file_fd(current_token, cur->in_file,
				&cmds->fd_in, &cmds->fd_heredoc) < 0)
			return (-1);
	}
	return (0);
}

void	set_cmd_path(t_command *cur, t_list_envp *env)
{
	char		*env_path;
	char		*tmp;

	env_path = get_ms_env_val(PATH, env);
	if (cur->build == -1)
	{
		tmp = cur->arg[0];
		cur->arg[0] = init_cmd_path(cur->arg[0],
				env_path);
		free(tmp);
	}
}

int	set_cmd_ready_to_exec(t_command **cmd, t_list_envp *env)
{
	t_command	*cur;
	int			ret_file;

	cur = *cmd;
	while (cur != NULL && cur->token != NWLINE)
	{
		ret_file = associate_file_to_cmd(cur);
		if (ret_file < 0)
			return (ret_file);
		set_builtin(cur->arg[0], cur);
		if (cur->token != NWLINE)
			set_cmd_path(cur, env);
		cur = cur->next;
	}
	return (0);
}

void	close_cmds_fd(t_command **cmds)
{
	t_command	*cmd;
	int			ret_in;
	int			ret_out;

	cmd = *cmds;
	ret_in = 0;
	ret_out = 0;
	(void)ret_in;
	(void)ret_out;
	while (cmd != NULL)
	{
		if (cmd->fd_in != -1)
			ret_in = close(cmd->fd_in);
		if (cmd->fd_out != -1)
			ret_out = close(cmd->fd_out);
		cmd = cmd->next;
	}
}
