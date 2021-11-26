//
// Created by antoine on 26/11/2021.
//

#ifndef MINISHELL_REDIR_H
#define MINISHELL_REDIR_H

#include "minishell.h"

typedef struct s_redir
{
	int		i;
	int		k;
	int		l;
	char	*var;
}				t_redir;

/* redir main */
int					redirection(t_split *split, t_command **cur, t_list_envp *ms_env);

/* redir ret */
int					ret_val(t_split *split, t_list_envp *ms_env);

/* redir get */
int					get_string(t_split *split, t_list_envp *ms_env, t_command **cur, int print);

#endif //MINISHELL_REDIR_H
