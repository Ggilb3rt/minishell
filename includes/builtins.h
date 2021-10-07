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

// Usually used env var
# define PWD "PWD="
# define OLDPWD "OLDPWD="

int	cmd_echo(char *str);
int	cmd_env(t_list_envp *ms_envp);
int	cmd_cd(char *path, t_list_envp *env);
int	cmd_pwd(t_list_envp *env, int print);
int	cmd_export(t_list_envp *env, char **args);
int	cmd_unset(t_list_envp **env, char **to_find);
int	builtin_exit(void);

#endif
