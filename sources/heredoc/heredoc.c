//
// Created by Antoine LANGLOIS on 27/10/2021.
//

#include "minishell.h"

void 	heredoc_func(char *arg, t_command **cmd)
{
	char *line;

	(void)arg;
	while (g_ret != 0)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		else if (!ms_strcmp(line, (*cmd)->heredoc))
		{
			g_ret = 0;
			break ;
		}
	}
}