//
// Created by Antoine LANGLOIS on 27/10/2021.
//

#include "minishell.h"

static int	event_hook(void)
{
	if (g_ret == QHERE)
	{
		rl_replace_line("\1", 1);
		rl_done = 1;
	}
	return (0);
}

void 	heredoc_func(char *arg, t_command **cmd)
{
	char *line;

	(void)arg;
	rl_event_hook = &event_hook;
	while (g_ret != QHERE)
	{
		printf("g_ret3 = %i\n", g_ret);
		line = readline("> ");
		if (line == NULL)
			break ;
		if (line[0] == '\1') {
			printf("g_ret4 = %i\n", g_ret);
			break;
		}
		else if (!ms_strcmp(line, (*cmd)->end))
		{
			g_ret = 0;
			break ;
		}
		else if (line)
		{
			//tmp_fd = open(cur->arg[0], O_CREAT | O_WRONLY | O_APPEND, 0666);
		}
	}
}