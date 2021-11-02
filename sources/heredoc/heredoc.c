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
	int		i;

	(void)arg;
	i = 0;
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
			t_simple_command *cur;
			int fd_out;
			char *out_file;

			fd_out = -1;
			out_file = (*cmd)->out_file;
			cur = (*(*cmd)->list);
			while (cur != NULL)
			{
				if (cur->token == DGREAT)
				{
					if (access(out_file, F_OK | R_OK) == -1)
						fd_out = open(out_file, O_WRONLY | O_RDONLY | O_APPEND | O_CREAT, 0666);
					else
						fd_out = open(out_file, O_WRONLY | O_RDONLY | O_APPEND, 0666);
				}
				if (cur->token == GREAT)
				{
					if (access(out_file, F_OK | R_OK) == -1)
					{
						fd_out = open(out_file, O_WRONLY | O_RDONLY | O_CREAT, 0666);
					}
					else
					{
						if (i == 0)
							fd_out = open(out_file, O_WRONLY | O_RDONLY, 0666);
						if (i > 0)
							fd_out = open(out_file, O_WRONLY | O_RDONLY | O_APPEND, 0666);
					}
					//printf("fd_out = %d\n")
				}
				cur = cur->next;
			}
			(*cmd)->fd_out = fd_out;
			(*cmd)->out_file = out_file;
			if ((*cmd)->fd_out == -1)
				perror("error");
			write((*cmd)->fd_out, line, ft_strlen(line));
			write((*cmd)->fd_out, "\n", 1);
			close((*cmd)->fd_out);
			i++;
		}
	}
}