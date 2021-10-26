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

int g_ret = 1;

void sig_handler(int n)
{
	if (n == SIGINT)
	{
		rl_on_new_line();
		printf("\n");
		g_ret = 2;
	}
	if (n == SIGQUIT)
	{
		printf("CTRL-slash detected\n");
	}
}

void ms_signal(void)
{
	if (signal(SIGINT, sig_handler) == SIG_ERR)
	{
		exit(1);
	}
	if (signal(SIGQUIT, sig_handler) == SIG_ERR)
	{
		exit(1);
	}
}

/*
static void init_cmd(t_command *cmd)
{
	cmd->numb_avail_simple_commands = 0;
	cmd->numb_simple_commands = 0;
	cmd->list = NULL;
	cmd->out_file = ms_strdup("dflt");
	cmd->in_file = ms_strdup("dflt");
	cmd->err_file = ms_strdup("dflt");
}
*/
int		count_until_pipe(t_simple_command **list)
{
	t_simple_command	*cur;
	int					count;

	cur = *list;
	count = 0;
	while (cur != NULL)
	{
		if (cur->token == PIPE)
			return (count);
		count++;
		cur = cur->next;
	}
	return (-1);
}

void	split_pipe(t_simple_command **list)
{
	int					count;
	t_simple_command	*cur;

	cur = *list;
	count = count_until_pipe(list);
	printf("count until pipe %d\n", count);
	while(count > 0)
	{
		for (int i = 0; cur->arg[i] != NULL; i++)
			printf("%s ", cur->arg[i]);
		cur = cur->next;
		count--;
	}
	printf("\n");
}

/*
int	main(int ac, char **av, char **envp)
{
	t_list_envp	*ms_envp;
	char		*line;
	char		*msg_prompt;
	t_command	*cmd;

	(void)ac;
	(void)av;
	cmd = malloc(sizeof(t_command));
	init_cmd(cmd);
	ms_signal();
	ms_envp = create_msenvp_lst(envp);
	
	msg_prompt = ms_strjoin(get_ms_env_val(USER, ms_envp), "@minishell > ");
	while (1)
	{
		line = readline(msg_prompt);
		if (!lexer_and_parser(line, cmd))
			break;
		if (line == NULL) {
			printf("\n");
			break ;
		}
		if ((g_ret = cmd_exit(line)) == 0)
			break ;
		if (line)
			add_history(line);
		print_simple_command(cmd->list);
		//split_pipe(cmd->list);
		associate_file_to_cmd(cmd->list);
	}
	free(msg_prompt);
	ms_lst_free_all(ms_envp);
	return (1);
}
*/



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
	cmd1[0] = init_cmd_path(cmd1[0], path);
	cmd2[0] = init_cmd_path(cmd2[0], path);
	cmd3[0] = init_cmd_path(cmd3[0], path);
	cmd4[0] = init_cmd_path(cmd4[0], path);
	char	**cmds[] = {cmd1, cmd2, cmd3, cmd4, NULL};
	int pid = pipeline(cmds, env);
	//ms_lst_free_all(ms_envp);
	//free_tab(env);
	//while (1)
	//{
		waitpid(pid, NULL, 0);
		line = readline("pouet | ");
	//}
	return (0); // return 0 or 1 ?
}
