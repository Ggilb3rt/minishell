/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alangloi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 21:59:50 by alangloi          #+#    #+#             */
/*   Updated: 2021/11/26 21:59:52 by alangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIR_H
# define REDIR_H

# include "minishell.h"

typedef struct s_redir
{
	int		i;
	int		k;
	int		l;
	char	*var;
}				t_redir;

/* redir main */
int		redirection(t_split *split, t_command **cur, t_list_envp *ms_env);

/* redir ret */
int		ret_val(t_split *split, t_list_envp *ms_env, int print);

/* redir get */
int		get_string(t_split *split, t_list_envp *ms_env,
			t_command **cur, int print);

#endif
