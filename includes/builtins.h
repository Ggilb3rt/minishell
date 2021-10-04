//
// Created by Antoine LANGLOIS on 22/09/2021.
//

#ifndef MINISHELL_COMMANDS_H
# define MINISHELL_COMMANDS_H

# include "minishell.h"

/* echo with option -n : echo 'string' */

/* cd with only a relative or absolute path */

/* pwd with no options */

/* export with no options : export 'name'='word' */

/* unset with no options or arguments : unset 'name' */

/* env with no options or arguments : env 'NAME'='value' */

/* exit with no options : exit 'n' */

int	cmd_echo(char *str);
int	cmd_env(t_list_envp *ms_envp);
int	cmd_cd(char *path, t_list_envp *env);
int	cmd_pwd(void);
int builtin_export(void);
int	builtin_unset(void);
int	builtin_exit(void);

#endif
