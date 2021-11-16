/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 15:33:48 by alangloi          #+#    #+#             */
/*   Updated: 2021/11/16 18:08:13 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_ret = 0;

void sig_handler(int n)
{
	if (n == SIGINT)
	{
		if (g_ret == EHERE)
		{
			g_ret = QHERE;
		}
		else
		{
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
			g_ret = 0;
		}
	}
}

void ms_signal(void)
{
	if (signal(SIGINT, sig_handler) == SIG_ERR)
	{
		exit(1);
	}
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	{
		exit(1);
	}
}

int	get_nb_cmds(t_command **cmds)
{
	int			i;
	t_command	*cmd;

	i = 0;
	cmd = *cmds;
	if (!cmd)
		return (-1);
	while (cmd != NULL)
	{
		if (cmd->list[0]->token == WORD)
			i++;
		cmd = cmd->next;
	}
	return (i);
}

void	close_cmds_fd(t_command **cmds)
{
	t_command	*cmd;
	int			ret_in;
	int			ret_out;

	cmd = *cmds;
	ret_in = 0;
	ret_out = 0;
	while (cmd != NULL)
	{
		if (cmd->fd_in != -1)
			ret_in = close(cmd->fd_in);
		if (cmd->fd_out != -1)
			ret_out = close(cmd->fd_out);
		//printf("fds_close %d, %d\n", ret_in, ret_out);
		cmd = cmd->next;
	}
}

static t_command **init_cmd(void)
{
	t_command **cmd;

	cmd = malloc(sizeof(t_command *));
	if (!cmd)
		return (NULL);
	*cmd = NULL;
	return (cmd);
}

int	main(int ac, char **av, char **envp)
{
	t_list_envp	*ms_envp;
	char		*line;
	char		*msg_prompt;
	t_command	**cmd;

	(void)ac;
	(void)av;
	line = ft_strdup("");
	ms_signal();
	ms_envp = create_msenvp_lst(envp);
	cmd_env(ms_envp);
	convert(ms_envp);
	msg_prompt = ft_strjoin(get_ms_env_val(USER, ms_envp), "@minishell > ");
	while (1)
	{
		free(line);
		cmd = NULL;
		cmd = init_cmd();
		line = readline(msg_prompt);
		if (!line)
			break ;
		else if (ft_strlen(line) > 0)
			add_history(line);
		else if (!ft_strcmp(line, ""))
			continue ;
		else
			free(line);
		if (!lexer_and_parser(line, cmd))
			break ;
		convert_var(cmd);
		if (g_ret == EHERE)
		{
			heredoc_func(line, cmd);
		}
		if ((g_ret = cmd_exit(line)) == 1)
			exit(0);
		set_cmd_ready_to_exec(cmd, ms_envp);
		//print_simple_command(cmd);
		//print_command(cmd);
		//print_all(cmd);
		// char **converted_ms_envp = convert_envplst_to_tab(ms_envp);
		// for(int p = 0; p < 30; p++)
		// {
		// 	printf("out %p, %s\n", converted_ms_envp[p], converted_ms_envp[p]);
		// }
		ms_pipeline(cmd, envp);
		close_cmds_fd(cmd);
		free_command(cmd);
		//free_tab(converted_ms_envp);
		//print_all(cmd);
	}
	if (cmd)
		free_command(cmd);
	printf("quit loop\n");
	//close_cmds_fd(cmd);
	free(msg_prompt);
	ms_lst_free_all(ms_envp);
	return (g_ret);
}
