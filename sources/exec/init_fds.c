/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 20:30:08 by ggilbert          #+#    #+#             */
/*   Updated: 2021/12/01 15:50:18 by ggilbert         ###   ########.fr       */
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

int	check_file_access(char *path, int *fd, int read_or_write)
{
	//printf("S'execute deux fois car utilisé dans le parsing et dans la préparation de cmd\n", path);
	if (access(path, F_OK | read_or_write) == -1)
	{
		*fd = -2;
		perror(path);
		return (0);
	}
	return (1);
}


int	init_in_file_fd(int cur_token, char *path, int *fd_in, int *fd_her)
{
	if (cur_token == LESS)
	{
		if (!check_read_access(path, fd_in))
			return (-1);
		if (*fd_her != -1)
			*fd_her = -1;
	}
	else if (cur_token == DLESS)
	{
		if (*fd_in != -1)
		{
			close(*fd_in);
			*fd_in = -1;
		}
		*fd_her = 0;
	}
	return (0);
}

int	init_out_file_fd(int cur_token, char *path, int *fd_out)
{
	if (cur_token == GREAT)
		*fd_out = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	else if (cur_token == DGREAT)
		*fd_out = open(path, O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (*fd_out == -1 && (cur_token == GREAT || cur_token == DGREAT))
	{
		*fd_out = -2;
		perror(path);
		return (-1);
	}
	return (0);
}
