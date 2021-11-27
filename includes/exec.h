//
// Created by Antoine LANGLOIS on 23/09/2021.
//

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

/* theses function will allow minishell to look for and run programs */

/* exec_cmd_path */
char		*init_cmd_path(char *cmd, char *paths);

/* exec */
void		exec_built_or_bin(t_command *cur, char **env, t_list_envp *lst);

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
