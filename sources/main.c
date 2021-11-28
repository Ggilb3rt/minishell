/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 15:33:48 by alangloi          #+#    #+#             */
/*   Updated: 2021/11/28 21:31:08 by ggilbert         ###   ########.fr       */
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
	//printf("create cmd %p\n", *cmd);
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

void free_all(t_command **cmd)
{
	t_command	*tmp;
	t_command	*cur;
	int			i;
	int			len;

	if (cmd)
	{
		cur = *cmd;
		while (cur)
		{
			if (cur->arg)
			{
				i = 0;
				len = array_size(cur->arg);
				while (i < len)
				{
					free(cur->arg[i]);
					cur->arg[i] = NULL;
					i++;
				}
				free(cur->arg);
				cur->arg = NULL;
			}
			cur = cur->next;
		}
		cur = *cmd;
		while (cur)
		{
			tmp = cur;
			cur = cur->next;
			free(tmp);
			tmp = NULL;
		}
		free(cmd);
		cmd = NULL;
	}
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
	ms_envp = create_msenvp_lst(envp);
	msg_prompt = ft_strjoin(get_ms_env_val(USER, ms_envp), " 🙌 minishell > ");
	//(void)pipeline_env;
	while (1)
	{
		line = readline(msg_prompt);
		if (line)
		{
			ms_signal(1);
			if (line[0] == '|')
			{
				printf("minishell: syntax error near unexpected token `|'\n");
				free(line);
				line = NULL;
				continue ;
			}
			if (ft_strlen(line) > 0)
			{
				cmd = NULL;
				if (init_cmd(&cmd))
				{
					add_history(line);
					if (parsing_main(line, cmd, ms_envp))
					{
						if (set_cmd_ready_to_exec(cmd, ms_envp) == 0)
						{
							pipeline_env = convert_envplst_to_tab(ms_envp);
							if (ms_pipeline(cmd, pipeline_env, ms_envp) == 0)
								close_cmds_fd(cmd);
						}
						free_tab(pipeline_env);
					}
					//print_all(cmd);
					free_all(cmd);
				}
			}
			else if (!ft_strcmp(line, ""))
				continue ;
			free(line);
			line = NULL;
			if (g_ret.quit == 1)
			{
				break ;
			}
		}
		else
			ms_signal(3);
	}
	//free_all(cmd);
	free(msg_prompt);
	ms_lst_free_all(ms_envp);
	//printf("ret before exit %d\n", g_ret.ret);
	return (g_ret.ret);
}
