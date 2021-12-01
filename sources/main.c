/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 15:33:48 by alangloi          #+#    #+#             */
/*   Updated: 2021/12/01 09:47:11 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_g_sig	g_ret = {.ret = 0, . quit = 0};

static void	launch_commands(char *line, t_list_envp *ms_envp)
{
	t_command	**cmd;
	char		**pipeline_env;

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
				free_tab(pipeline_env);
			}
		}
		free_all(cmd);
	}
}

static int	interpret_line(char *line, t_list_envp *ms_envp)
{
	if (line[0] == '|')
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		free(line);
		line = NULL;
		return (1);
	}
	if (ft_strlen(line) > 0)
		launch_commands(line, ms_envp);
	else if (!ft_strcmp(line, ""))
		return (1);
	free(line);
	line = NULL;
	if (g_ret.quit == 1)
		return (0);
	return (1);
}

static int	get_line(t_list_envp *ms_envp, char *msg_prompt)
{
	char	*line;

	ms_signal(1);
	line = readline(msg_prompt);
	if (line)
	{
		if (!interpret_line(line, ms_envp))
			return (0);
	}
	else
		ms_signal(3);
	return (1);
}

static void	print_message(void)
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
	char		*msg_prompt;

	(void)ac;
	(void)av;
	print_message();
	ms_envp = create_msenvp_lst(envp);
	msg_prompt = ft_strjoin(get_ms_env_val(USER, ms_envp), " 🙌 minishell > ");
	while (1)
	{
		if (!get_line(ms_envp, msg_prompt))
			break ;
	}
	free(msg_prompt);
	ms_lst_free_all(ms_envp);
	return (g_ret.ret);
}
