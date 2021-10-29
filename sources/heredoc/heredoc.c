//
// Created by Antoine LANGLOIS on 27/10/2021.
//

#include "minishell.h"

static int	event_hook(void)
{
	if (g_ret == 2)
	{
		rl_replace_line("\3", 1);
		rl_done = 1;
	}
	return (0);
}

void 	heredoc_func(char *arg, t_command **cmd)
{
	char *line;

	(void)arg;
	rl_event_hook = &event_hook;
	while (g_ret != 2)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (line[0] == '\3')
			break ;
		else if (!ms_strcmp(line, (*cmd)->heredoc))
		{
			g_ret = 0;
			break ;
		}
		else if (line)
		{
			tmp_fd = open(cur->arg[0], O_CREAT | O_WRONLY | O_APPEND, 0666);
		}
	}
}