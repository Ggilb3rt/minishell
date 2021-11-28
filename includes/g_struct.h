/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_struct.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 14:48:32 by ggilbert          #+#    #+#             */
/*   Updated: 2021/11/28 14:49:36 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef G_STRUCT_H
# define G_STRUCT_H

# define QEXIT 0
# define EHERE -1
# define QHERE -2

# define IN 0
# define OUT 1

# define BUILT_ECHO 0
# define BUILT_PWD 1
# define BUILT_ENV 2

# define BUILT_CD 10
# define BUILT_EXPORT 11
# define BUILT_UNSET 12
# define BUILT_EXIT 13

typedef struct s_list_envp
{
	char				*content;
	struct s_list_envp	*next;
}	t_list_envp;

typedef struct s_g_sig
{
	int					ret;
	int					quit;
}	t_g_sig;

typedef struct s_command
{
	int					nb_cmd;
	int					token_in;
	int					token_out;
	int					token;
	char				**arg;
	char				*out_file;
	char				*in_file;
	int					fd_in;
	int					fd_out;
	char				*end;
	int					build;
	int					can_exec;
	struct s_command	*next;
}				t_command;

#endif