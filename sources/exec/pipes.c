/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 08:27:26 by ggilbert          #+#    #+#             */
/*   Updated: 2021/11/27 17:36:25 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_pipe(int *fd)
{
	if (pipe(fd) != 0)
	{
		perror("pipe");
		return (-1);
	}
	return (0);
}

void	close_pipe(int *pipe_fd)
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}
