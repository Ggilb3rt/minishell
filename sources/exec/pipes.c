/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 08:27:26 by ggilbert          #+#    #+#             */
/*   Updated: 2021/11/22 08:27:45 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_pipe(int *fd)
{
	if (pipe(fd) != 0)
	{
		perror("pipe");
		exit(errno);
	}
}

void	process_pipe(int *fd, int fd_in)
{
	close(fd[1]);
	if (fd_in != -1)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	else
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
	ms_pipe(fd);
}
