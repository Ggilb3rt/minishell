/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alangloi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 17:34:10 by alangloi          #+#    #+#             */
/*   Updated: 2021/11/29 17:34:11 by alangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler_1(int n)
{
	if (n == SIGINT)
	{
		if (g_ret.ret == EHERE)
			g_ret.ret = QHERE;
		else
		{
			g_ret.ret = 130;
			printf("\n");
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
	}
}

void	sig_handler_2(int n)
{
	if (n == SIGINT)
	{
		g_ret.ret = 130;
		printf("\n");
	}
	else if (n == SIGQUIT)
	{
		g_ret.ret = 131;
		printf("Quit (core dumped)\n");
	}
}

void	ms_signal(int n)
{
	if (n == 1)
	{
		if (signal(SIGINT, sig_handler_1) == SIG_ERR)
			exit(1);
		if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
			exit(1);
	}
	if (n == 2)
	{
		if (signal(SIGINT, sig_handler_2) == SIG_ERR)
			exit(1);
		if (signal(SIGQUIT, sig_handler_2) == SIG_ERR)
			exit(1);
	}
	if (n == 3)
	{
		printf("exit\n");
		exit(0);
	}
}