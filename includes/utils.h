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
void		free_tab_2(char **arr);
void		free_command(t_command **cmd);
//void		free_split(t_split *split);


#endif
