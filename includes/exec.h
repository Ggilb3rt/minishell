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
int			**create_pipes_fd(int nb_pipe);
//int			ms_pipeline2(char ***cmd, char **env);
int			ms_pipeline(t_command **cmd, char **env, t_list_envp *lst);
//void		new_pipeline(t_command **cmds);

/* prepare_cmds.c */
int			associate_file_to_cmd(t_command *cmds);
int			set_cmd_ready_to_exec(t_command **cmd, t_list_envp *env_path);

/* pipes.c */
int			ms_pipe(int *fd);
void		process_pipe(int *fd, int fd_in);

#endif
