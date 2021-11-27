/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 15:33:48 by alangloi          #+#    #+#             */
/*   Updated: 2021/11/27 17:56:35 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_g_sig	g_ret = {.ret = 0, . quit = 0};

void	sig_handler_1(int n)
{
	if (n == SIGINT)
	{
		if (g_ret.ret == EHERE)
			g_ret.ret = QHERE;
		else
		{
			g_ret.ret = 130;
			printf("\n");
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
	}
}

void	sig_handler_2(int n)
{
	if (n == SIGINT)
	{
		g_ret.ret = 130;
		printf("\n");
	}
	else if (n == SIGQUIT)
	{
		g_ret.ret = 131;
		printf("Quit (core dumped)\n");
	}
}

void	ms_signal(int n)
{
	if (n == 1)
	{
		if (signal(SIGINT, sig_handler_1) == SIG_ERR)
			exit(1);
		if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
			exit(1);
	}
	if (n == 2)
	{
		if (signal(SIGINT, sig_handler_2) == SIG_ERR)
			exit(1);
		if (signal(SIGQUIT, sig_handler_2) == SIG_ERR)
			exit(1);
	}
	if (n == 3)
	{
		printf("exit\n");
		exit(0);
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
		if (cmd->token == WORD)
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
	(void)ret_in;
	(void)ret_out;
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

static int	init_cmd(t_command ***cmd)
{
	*cmd = malloc(sizeof(t_command *));
	if (!*cmd)
		return (0);
	**cmd = NULL;
	return (1);
}

static void print_message(void)
{
	printf("++++++++++++++++++++++++++++++++++++++++++++++++\n");
	printf("+                                              +\n");
	printf("+        Minishell by Moulage Lituanien        +\n");
	printf("+                                              +\n");
	printf("++++++++++++++++++++++++++++++++++++++++++++++++\n");
}

int	main(int ac, char **av, char **envp)
{
	t_list_envp	*ms_envp;
	char		*line;
	char		*msg_prompt;
	t_command	**cmd;
	char		**pipeline_env;

	(void)ac;
	(void)av;
	print_message();
	line = ft_strdup("");
	ms_signal(1);
	ms_envp = create_msenvp_lst(envp);
	msg_prompt = ft_strjoin(get_ms_env_val(USER, ms_envp), " 🙌 minishell > ");
	while (1)
	{
		line = readline(msg_prompt);
		if (line)
		{
			if (ft_strlen(line) > 0)
			{
				cmd = NULL;
				init_cmd(&cmd);
				add_history(line);
				if (parsing_main(line, cmd, ms_envp))
				{
					set_cmd_ready_to_exec(cmd, ms_envp);
					pipeline_env = convert_envplst_to_tab(ms_envp);
					ms_pipeline(cmd, pipeline_env, ms_envp);
					close_cmds_fd(cmd);
					free_tab(pipeline_env);
				}
				free_command(cmd);
			}
			else if (!ft_strcmp(line, ""))
				continue ;
			if (g_ret.ret == EHERE)
				heredoc_func(line, cmd);
			if (g_ret.quit == 1)
				break ;
			free(line);
		}
		else
			ms_signal(3);
	}
	close_cmds_fd(cmd);
	free_command(cmd);
	free(line);
	free(msg_prompt);
	ms_lst_free_all(ms_envp);
	return (g_ret.ret);
}
