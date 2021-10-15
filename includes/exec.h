//
// Created by Antoine LANGLOIS on 23/09/2021.
//

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

/* theses function will allow minishell to look for and run programs */
char		**convert_envplst_to_tab(t_list_envp *ms_env);
char		*init_cmd_path(char *cmd, char *paths);
int			**create_pipes_fd(int nb_pipe);
void		pipeline(char ***cmd, char **env);

#endif
