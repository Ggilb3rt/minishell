//
// Created by Antoine LANGLOIS on 27/10/2021.
//

#include "minishell.h"

static int	event_hook(void)
{
	if (g_ret.ret == QHERE)
	{
		rl_replace_line("\1", 1);
		rl_done = 1;
	}
	return (0);
}

void	heredoc_func(char *arg, t_command **cmd)
{
	char	*line;
	int		fd;

	(void)arg;
	rl_event_hook = &event_hook;
	line = ft_strdup("");
	fd = open((*cmd)->end, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	printf("hello darkness my old friend %d\n", fd);
	while (g_ret.ret != QHERE)
	{
		free(line);
		line = readline("> ");
		if (line == NULL)
			break ;
		if (line[0] == '\1')
			break ;
		else if (!ft_strcmp(line, (*cmd)->end))
		{
			g_ret.ret = 0;
			break ;
		}
		else if (line && ft_strlen(line) != ft_strlen((*cmd)->end))
		{
			if (fd == -1)
				perror("error");
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
		}
	}
	close(fd);
	free(line);
	(*cmd)->fd_in = open((*cmd)->end, O_RDONLY | O_CREAT, 0777);
	unlink((*cmd)->end);
	//utiliser dup 2 mettre end dans in
}
