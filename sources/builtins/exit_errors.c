/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 17:56:16 by ggilbert          #+#    #+#             */
/*   Updated: 2021/12/02 17:56:35 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	too_many_arg_err(int print)
{
	g_ret.ret = 1;
	g_ret.quit = 0;
	if (print)
		printf("minishell: exit: too many arguments\n");
	return (1);
}

int	not_numeric_arg_err(char *arg, int print)
{
	g_ret.ret = 2;
	g_ret.quit = 1;
	if (print)
		printf("minishell : exit : %s: numeric argument required\n", arg);
	return (255);
}
