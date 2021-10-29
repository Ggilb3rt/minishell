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
char		**convert_envplst_to_tab(t_list_envp *ms_env);
int			**create_pipes_fd(int nb_pipe);
int			ms_pipeline(char ***cmd, char **env);
void		new_pipeline(t_command **cmds);

/* prepare_cmds */
int			associate_file_to_cmd(t_simple_command **list);

#endif
