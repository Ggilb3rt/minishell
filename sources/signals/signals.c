//
// Created by Antoine LANGLOIS on 20/10/2021.
//

#include "minishell.h"

void sig_handler(int n)
{
	if (n == SIGQUIT)
		g_sig.ret = 2;
}

void ms_signal(void)
{
	if (signal(SIGINT, sig_handler) == SIG_ERR)
	{
		exit(1);
	}
	if (signal(SIGQUIT, sig_handler) == SIG_ERR)
	{
		exit(1);
	}
}