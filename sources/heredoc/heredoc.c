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

char	*create_tmp_file_name(char *str, int nb)
{
	char	*file_name;
	char	*file_nb;

	file_nb = ft_itoa(nb);
	file_name = ft_strjoin(str, file_nb);
	free(file_nb);
	return (file_name);
}

void	heredoc_func(char *arg, t_command *cmd)
{
	char	*line;
	char	*file_name;
	int		fd;

	(void)arg;
	//ms_signal(4);
	rl_event_hook = &event_hook;
	line = ft_strdup("");
	file_name = create_tmp_file_name(".mini_heredoc", cmd->nb_cmd);
	fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	while (g_ret.ret != QHERE)
	{
		free(line);
		line = readline("> ");
		if (line == NULL)
			break ;
		if (line[0] == '\1')
			break ;
		else if (!ft_strcmp(line, cmd->end))
		{
			g_ret.ret = 0;
			break ;
		}
		else if (line && ft_strlen(line) != ft_strlen(cmd->end))
		{
			if (fd == -1)
				perror("error");
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
		}
	}
	close(fd);
	free(line);
	cmd->fd_heredoc = open(file_name, O_RDONLY | O_CREAT, 0777);
	unlink(file_name);
	free(file_name);
	//utiliser dup 2 mettre end dans in
}

/*

ctrl + d ==> send EOF
if heredoc EOF != EOF print : warning: here-document at line 2 delimited by end-of-file (wanted `out')

ctrl + c ==> quit


La difference entre les deux est que le premier continue l'execution (print le resultat)
alors que le second quit l'execution (ne print rien)
*/