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
	char	*line;

	(void)arg;
	rl_event_hook = &event_hook;
	line = ft_strdup("");
	(*cmd)->fd_out = open((*cmd)->end, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	while (g_ret != QHERE)
	{
		free(line);
		line = readline("> ");
		if (line == NULL)
			break ;
		if (line[0] == '\1')
		{
			break;
		}
		else if (!ft_strcmp(line, (*cmd)->end))
		{
			g_ret = 0;
			break ;
		}
		else if (line && ft_strlen(line) != ft_strlen((*cmd)->end))
		{
			if ((*cmd)->fd_out == -1)
				perror("error");
			write((*cmd)->fd_out, line, ft_strlen(line));
			write((*cmd)->fd_out, "\n", 1);
		}
	}
	close((*cmd)->fd_out);
}
