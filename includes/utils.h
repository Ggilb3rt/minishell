/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alangloi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 21:59:12 by alangloi          #+#    #+#             */
/*   Updated: 2021/11/26 21:59:13 by alangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

int			array_size(char **arr);
int			arr_int_size(int *arr);

void		free_tab(char **arr);
void		free_command(t_command **cmd);
void		free_split(t_split *split);
//void	free_command(t_command *cmd);
//void 	free_simple_command(t_simple_command **list);

/*
 * utils 5
 * env handler
 */
//char		*get_env_val(char *to_find, char **env);

//char		*get_env_val(char *to_find, char **env);
//int		get_env_index(char *to_find, char **env);
//size_t		get_ms_env_len(t_list_envp *ms_env);
//char		*get_ms_env_val(char *to_find, t_list_envp *ms_env);
//int			get_ms_env_index(char *to_find, t_list_envp *ms_env);
//t_list_envp	*ms_lst_point(int index, t_list_envp *ms_env);
//int			ft_isdigit(int c);
//int			ft_isalpha(int c);
//int			ft_isalnum(int c);
//int			ms_str_isalnum_under(char *s);
//char		*ms_strchr(const char *s, int c);

#endif
