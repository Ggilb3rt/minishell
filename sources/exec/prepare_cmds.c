/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 11:12:42 by ggilbert          #+#    #+#             */
/*   Updated: 2021/10/29 16:49:54 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_read_access(char *path, int *fd)
{
	//printf("path %s\n", path);
	if (access(path, F_OK | R_OK) == -1)
	{
		*fd = -2;
		perror("access");
		return (0);
	}
	*fd = open(path, O_RDONLY);
	//printf("check fd in access in file %d\n", *fd);
	return (1);
}

/*
* L'acces, la creation et le append sur les fichiers fonctionnent
*/
int	associate_file_to_cmd_b(t_simple_command **list)
{
	t_simple_command	*cur;
	int					current_token;
	int					tmp_fd;

	cur = *list;
	tmp_fd = 0;
	while (cur != NULL)
	{
		current_token = cur->token;
		if (current_token == GREAT || current_token == DGREAT
			|| current_token == LESS || current_token == DLESS)
		{
			cur = cur->next;
			if (cur->token != WORD)
				return (-1);
			if (current_token == LESS)
			{
				if (!check_read_access(cur->arg[0], &tmp_fd))
					return (-1);
			}
			else if (current_token == GREAT)
				tmp_fd = open(cur->arg[0], O_CREAT | O_WRONLY, 0666);
			else if (current_token == DGREAT)
				tmp_fd = open(cur->arg[0], O_CREAT | O_WRONLY | O_APPEND, 0666);
			else if (current_token == DLESS)
				tmp_fd = 1;
			if (tmp_fd == -1)
			{
				perror("open");
				return (errno);
			}
			if (tmp_fd > 0)
				write(tmp_fd, "Loeut\n", 7);
			printf("tmp fd : %d\n", tmp_fd);
		}
		cur = cur->next;
	}
	return (0);
}

int	init_files_fds(int prev_token, char *path, int *fd_in, int *fd_out)
{
	if (prev_token == LESS)
	{
		if (!check_read_access(path, fd_in))
			return (-1);
	}
	else if (prev_token == DLESS)
		*fd_in = 1;
	else if (prev_token == GREAT)
		*fd_out = open(path, O_CREAT | O_WRONLY, 0666);
	else if (prev_token == DGREAT)
		*fd_out = open(path, O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (*fd_out == -1)
	{
		perror("open");
		return (errno);
	}
	return (0);
}

int	associate_file_to_cmd(t_command *cmds)
{
	t_simple_command	*cur;
	int					current_token;
	//int					tmp_fd;

	cur = cmds->list[0];
	//tmp_fd = 0;
	while (cur != NULL)
	{
		current_token = cur->token;
		if (current_token == GREAT || current_token == DGREAT
			|| current_token == LESS || current_token == DLESS)
		{
			cur = cur->next;
			if (cur->token != WORD)
				return (-2);
			if (init_files_fds(current_token, cur->arg[0],
					&cmds->fd_in, &cmds->fd_out) < 0)
				return (-1);
		}
		cur = cur->next;
	}
	return (0);
}

int	set_cmd_ready_to_exec(t_command **cmd)
{
	t_command	*cur;
	int			ret_file;

	cur = *cmd;
	while (cur != NULL)
	{
		ret_file = associate_file_to_cmd(cur);
		if (ret_file < 0)
			return (ret_file);
		cur = cur->next;
	}
	return (0);
}