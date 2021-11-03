#include "minishell.h"

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
	int	i;

	i = 0;
	if (!cmds)
		return (-1);
	while (*cmds != NULL)
	{
		if ((*cmds)->list[0]->token == WORD)
			i++;
		*cmds = (*cmds)->next;
	}
	return (i);
}

void base_pour_exec(t_command **cmd, char **env)
{
	char	***options;
	int		nb_cmds;
	int		i;
	int		fd[2];
	//int		ret_file;

	fd[0] = -1;
	fd[1] = -1;
	i = 0;
	nb_cmds = get_nb_cmds(cmd);
	// ici cmd est sur le pointeur null à la fin ...
	options = malloc(sizeof(options) * (nb_cmds + 1));
	if (!options)
		return ;
	//! si ```ls < in | cqt > out | grep > out | ls``` return 3 (bug with cqt > out), ```cqt < out``` is ok...
	//! le bug vient du parser en fait, si une cmd n'est pas detectée correctement
	//printf("nb %d\n", nb_cmds);
	// malloc ***options with nb of cmds
	// options = {{"lol", "internet", NULL}, {"ls", "-la", "oput", NULL}, NULL}
	// replace "/" (= 7) by NULL
	while (*cmd != NULL)
	{
		//ret_file = associate_file_to_cmd(*cmd);
		options[i] = (*cmd)->list[0]->arg;
		fd[0] = (*cmd)->fd_in;
		fd[1] = (*cmd)->fd_out;
		*cmd = (*cmd)->next;
		i++;
	}
	//printf("i %d\n", i);
	options[i] = NULL;
	for (int i = 0; options[i] != NULL; i++)
	{
		for (int j = 0; options[j] != NULL; j++)
			printf("option[%d] : %s | fd_in : %d | fd_out : %d\n", i, options[i][j], fd[0], fd[1]);
	}
	(void)env;
	// infinit while
	//ms_pipeline(&options, env);
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
	ms_signal();
	line = ft_strdup("");
	ms_envp = create_msenvp_lst(envp);
	msg_prompt = ft_strjoin(get_ms_env_val(USER, ms_envp), "@minishell > ");
	while (1)
	{
		free(line);
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
		if (g_ret == EHERE)
		{
			heredoc_func(line, cmd);
		}
		if ((g_ret = cmd_exit(line)) == 1)
			exit(0);
		set_cmd_ready_to_exec(cmd);
		//print_simple_command(cmd);
		//print_command(cmd);
		//print_all(cmd);
		char	**my_env = convert_envplst_to_tab(ms_envp);
		base_pour_exec(cmd, my_env);
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