#include "minishell.h"

/*
 * create the loop that will run minishell
 */

/*
 * create the loop that will run minishell
 */

/*
 * Utiliser variable globale pour CTRL-D CTRL-C CTRL-\
 */

int g_ret = 0;

void sig_handler(int n)
{
	if (n == SIGINT)
	{
		if (g_ret != 2)
		{
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		g_ret = 0;
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

void letest(t_command **cmd)
{
	char	**options;
	int		fd[2];
	int		ret_file;

	fd[0] = -1;
	fd[1] = -1;
	while (*cmd != NULL)
	{
		ret_file = associate_file_to_cmd2(*cmd);
		options = (*cmd)->list[0]->arg;
		fd[0] = (*cmd)->fd_in;
		fd[1] = (*cmd)->fd_out;
		for (int i = 0; options[i] != NULL; i++)
			printf("option[%d] : %s | fd_in : %d | fd_out : %d\n", i, options[i], fd[0], fd[1]);
		printf("ret_file = %d\n", ret_file);
		*cmd = (*cmd)->next;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_list_envp	*ms_envp;
	char		*line;
	char		*msg_prompt;
	t_command	**cmd;

	(void)ac;
	(void)av;
	cmd = malloc(sizeof(t_command *));
	//init_cmd(cmd);
	ms_signal();

	ms_envp = create_msenvp_lst(envp);
	//msg_prompt = ms_strjoin(get_ms_env_val(USER, ms_envp), "@minishell > ");
	while (1)
	{
		msg_prompt = ms_strjoin(get_ms_env_val(USER, ms_envp), "@minishell > ");
		line = readline(msg_prompt);
		if (!lexer_and_parser(line, cmd))
			break ;
		if (g_ret == 2)
			heredoc_func(line, cmd);
		if (!line)
			cmd_exit(line);
		else if (ms_strlen(line) > 0)
			add_history(line);
		else
			free(line);
		if ((g_ret = cmd_exit(line)) == 0)
			exit(0);
		//print_simple_command(cmd);
		//print_command(cmd);
		print_all(cmd);

		letest(cmd);

	}
	free(msg_prompt);
	ms_lst_free_all(ms_envp);
	return (g_ret);
}


/*
int	main(int ac, char **av, char **envp)
{
	t_list_envp	*ms_envp;
	char		*line;
	//char		*msg_prompt;
	//t_command *cmd;

	(void)ac;
	(void)av;
	//cmd = malloc(sizeof(t_command));
	//init_cmd(cmd);
	ms_envp = create_msenvp_lst(envp);
	char	**env = convert_envplst_to_tab(ms_envp);
	(void)env;

	char	*path = get_ms_env_val(PATH, ms_envp);
	char	**cmd1 = ms_split("cat", ' ');
	char	**cmd2 = ms_split("cat", ' ');
	char	**cmd3 = ms_split("cat", ' ');
	char	**cmd4 = ms_split("ls", ' ');
	char	**cmd1 = ms_split("ls -la", ' ');
	char	**cmd2 = ms_split("grep 26", ' ');
	char	**cmd3 = ms_split("tr 20 @", ' ');
	char	**cmd4 = ms_split("tr @ !", ' ');
	cmd1[0] = init_cmd_path(cmd1[0], path);
	cmd2[0] = init_cmd_path(cmd2[0], path);
	cmd3[0] = init_cmd_path(cmd3[0], path);
	cmd4[0] = init_cmd_path(cmd4[0], path);
	char	**cmds[] = {cmd1, cmd2, cmd3, cmd4, NULL};
	//for (int i = 0; cmds[i] != NULL; i++)
	//	printf("%s %s %s\n", cmds[i][0], cmds[i][1], cmds[i][2]);
	//ms_lst_free_all(ms_envp);
	//free_tab(env);
	while (1)
	{
		line = readline("====> ");
		if (line[0] == 'q')
			return (1);
		if (line[0] == 'c')
			ms_pipeline(cmds, env);
		printf("==");
	}
	free_tab(env);
	ms_lst_free_all(ms_envp);
	return (0); // return 0 or 1 ?
}
*/