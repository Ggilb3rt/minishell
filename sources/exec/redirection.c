/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 17:40:26 by ggilbert          #+#    #+#             */
/*   Updated: 2021/11/28 16:21:36 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	set_redir(t_command *cur, int *old_pipe, int *new_pipe)
// {
// 	if (cur->fd_in != -1)
// 	{
// 		close(pipe_fd[1]);
// 		dup2(cur->fd_in, STDIN_FILENO);
// 		close(cur->fd_in);
// 	}
// 	if (cur->fd_out != -1)
// 	{
// 		close(pipe_fd[0]);
// 		dup2(cur->fd_out, STDOUT_FILENO);
// 		close(cur->fd_out);
// 	}
// }

void	set_redir(t_command *cur, int pipe_fd[2])
{
	if (cur->end != NULL)
	{
		heredoc_func("pouet", cur);
	}
	if (cur->fd_heredoc != -1)
	{
		close(pipe_fd[1]);
		dup2(cur->fd_heredoc, STDIN_FILENO);
		close(cur->fd_heredoc);
	}
	if (cur->fd_in != -1)
	{
		close(pipe_fd[1]);
		dup2(cur->fd_in, STDIN_FILENO);
		close(cur->fd_in);
	}
	if (cur->fd_out != -1)
	{
		close(pipe_fd[0]);
		dup2(cur->fd_out, STDOUT_FILENO);
		close(cur->fd_out);
	}
}
