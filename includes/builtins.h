/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 21:59:28 by alangloi          #+#    #+#             */
/*   Updated: 2021/12/02 17:58:16 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

/* echo with option -n : echo 'string' */

/* cd with only a relative or absolute path */

/* pwd with no options */

/* export with no options : export 'name'='word' */

/* unset with no options or arguments : unset 'name' */

/* env with no options or arguments : env */

/* exit with no options : exit 'n' */

// Usually used env var
# define USER "USER="
# define PWD "PWD="
# define OLDPWD "OLDPWD="
# define PATH "PATH="
# define HOME "HOME="

/* exit_error.c */
int			too_many_arg_err(int print);
int			not_numeric_arg_err(char *arg, int print);

int			cmd_echo(char **words);
int			cmd_env(t_list_envp *ms_env);
int			cmd_cd(char **path, t_list_envp *env);
int			cmd_pwd(t_list_envp *env, int print);
int			cmd_export(t_list_envp *env, char **args, int print);
int			cmd_unset(t_list_envp **env, char **to_find);
int			cmd_exit(char **args, t_command *cur, int print);
int			exec_builtin(char **cmd_name, t_list_envp *env,
                            int print, t_command *cur);
void		set_builtin(char *cmd_name, t_command *cur);
#endif
