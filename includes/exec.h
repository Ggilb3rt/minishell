/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 21:58:32 by alangloi          #+#    #+#             */
/*   Updated: 2021/11/28 21:05:02 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

typedef struct s_token
{
	int		in;
	int		out;
}			t_token;

typedef struct s_pipes
{
	int		old_pipe[2];
	int		new_pipe[2];
}	t_pipes;

/* exec_cmd_path */
char		*init_cmd_path(char *cmd, char *paths);

/* exec */
int			exec_built_or_bin(t_command *cur, char **env, t_list_envp *lst);

int			init_in_file_fd(int cur_token, char *path, int *fd_in, int *fd_her);
int			init_out_file_fd(int cur_token, char *path, int *fd_out);

/* init_fds.c */
int			init_out_file_fd(int cur_token, char *path, int *fd_out);
int			init_in_file_fd(int cur_token, char *path, int *fd_in, int *fd_her);

/* prepare_cmds.c */
int			associate_file_to_cmd(t_command *cmds);
int			set_cmd_ready_to_exec(t_command **cmd, t_list_envp *env_path);

/* pipes.c */
int			ms_pipe(int *fd);
void		close_pipe(int *fd);

/* pipeline.c */
int			ms_pipeline(t_command **cmd, char **env, t_list_envp *lst);

/* redirection.c */
void		set_redir(t_command *cur, int pipe_fd[2]);

#endif
