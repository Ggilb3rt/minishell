/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alangloi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 21:58:58 by alangloi          #+#    #+#             */
/*   Updated: 2021/11/26 21:59:00 by alangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "minishell.h"

// env_exec
char		**convert_envplst_to_tab(t_list_envp *ms_env);
char		**convert(t_list_envp *ms_env);

// env_edit
void		edit_lst_content(t_list_envp *env, int index, char *new_val);
void		ms_lst_push_end(t_list_envp **alst, t_list_envp *new);
int			ms_lst_pop_end(t_list_envp *head);
void		ms_lst_pop_inside(t_list_envp *current, t_list_envp *prev);
t_list_envp	*ms_lst_pop_first(t_list_envp *head);

// env_free
void		remove_lst_content(char *content);
void		ms_lst_free_all(t_list_envp *head);

// env
void		print_envp(t_list_envp *head, int export);
t_list_envp	*new_char_list(char *str);
t_list_envp	*create_msenvp_lst(char **envp);

//env var
void		convert_var(t_command **cmd, t_list_envp *ms_env);

/* ENV */
char		*get_env_val(char *to_find, char **env);

//char		*get_env_val(char *to_find, char **env);
//int		get_env_index(char *to_find, char **env);
int			get_ms_env_len(t_list_envp *ms_env);
char		*get_ms_env_val(char *to_find, t_list_envp *ms_env);
int			get_ms_env_index(char *to_find, t_list_envp *ms_env);
t_list_envp	*ms_lst_point(int index, t_list_envp *ms_env);

#endif
