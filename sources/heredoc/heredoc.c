/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alangloi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 17:34:39 by alangloi          #+#    #+#             */
/*   Updated: 2021/11/29 17:34:40 by alangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static int	handle_heredoc(char *line, t_command **cmd, int fd)
{
	if (line[0] == '\1')
		return (0);
	else if (ft_strcmp(line, (*cmd)->end))
	{
		if (fd == -1)
			perror("error");
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
	}
	else
	{
		g_ret.ret = 0;
		return (0);
	}
	return (1);
}

static int	get_heredoc(t_command **cmd, int fd, char *line)
{
	ms_signal(1);
	line = readline("> ");
	if (line == NULL)
	{
		printf("bash: warning: here-document at line 8 delimited by end-of-file (wanted `%s')\n", (*cmd)->end);
		return (0);
	}
	if (!handle_heredoc(line, cmd, fd))
	{
		free(line);
		line = NULL;
		return (0);
	}
	free(line);
	line = NULL;
	return (1);
}


int	heredoc_func(t_command **cmd)
{
	char	*file_name;
	int		fd;
	char	*line;

	line = ft_strdup("");
	rl_event_hook = &event_hook;
	file_name = create_tmp_file_name(".mini_heredoc", (*cmd)->nb_cmd);
	fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	while (g_ret.ret != QHERE)
	{
		if (!get_heredoc(cmd, fd, line))
			break ;
	}
	if (g_ret.ret == QHERE)
		g_ret.ret = 130;
	close(fd);
	(*cmd)->fd_heredoc = open(file_name, O_RDONLY | O_CREAT, 0777);
	unlink(file_name);
	free(file_name);
	file_name = NULL;
	return (1);
}