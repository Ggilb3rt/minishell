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
	int 	ret;

	(void)arg;
	rl_event_hook = &event_hook;
	while (g_ret != QHERE)
	{
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
		else if (line)
		{
			printf("out file = %s, fd out = %d\n", (*cmd)->out_file, (*cmd)->fd_out);
			ret = open((*cmd)->out_file, O_WRONLY | O_RDONLY | O_APPEND, 0666);
			if (!ret)
				return ;
			write((*cmd)->fd_out, line, ft_strlen(line));
			close((*cmd)->fd_out);
			//-------------------------------------------------
			FILE *ptr = fopen((*cmd)->out_file, "r");
			if (ptr == NULL)
			{
				printf("cant open file\n");
				exit(0);
			}
			char c = fgetc(ptr);
			while (c != EOF)
			{
				printf("%c", c);
				c = fgetc(ptr);
			}
			fclose(ptr);
			//-------------------------------------------------
		}
	}
}