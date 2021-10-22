#include "minishell.h"

/*
int	main(int ac, char **av, char **envp)
{
	t_list_envp	*ms_envp;
	char		*line;
	char		*msg_prompt;
	t_command *cmd;

	(void)ac;
	(void)av;
	cmd = malloc(sizeof(t_command));
	init_cmd(cmd);
	ms_envp = create_msenvp_lst(envp);

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
	//char	**env = convert_envplst_to_tab(ms_envp);
	pipeline(cmds, envp);
	//(void)env;
	ms_lst_free_all(ms_envp);
	//free_tab(env);
	return (0); // return 0 or 1 ?
}
*/

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

static void init_cmd(t_command *cmd)
{
	cmd->numb_avail_simple_commands = 0;
	cmd->numb_simple_commands = 0;
	cmd->list = NULL;
	cmd->out_file = ms_strdup("dflt");
	cmd->in_file = ms_strdup("dflt");
	cmd->err_file = ms_strdup("dflt");
}

//ret = {{"ls", "la"}, {"cd"}, {"grep", "poeut"}}
//char ** == {"ls", "la"}
// char * == "ls"
char	***pass_cmds_to_exec(t_command *cmds)
{
	t_simple_command	*cur;
	int					i;
	int					count;
	int					arr_size;
	char				***ret;

	arr_size = 0;
	count = 0;
	cur = *cmds->list;
	ret = malloc(sizeof(ret) * (cmds->numb_simple_commands));
	while (cur != NULL)
	{
		i = 0;
		arr_size = array_size(cur->arg) + 1;
		printf("arr_size %d\n", arr_size);
		while (i < arr_size)
		{
			printf("%d, %s ; ", i, cur->arg[i]);
			i++;
		}
		printf("\n");
		cur = cur->next;
		count++;
	}
	return (ret);
}

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
	}
	free(msg_prompt);
	ms_lst_free_all(ms_envp);
	return (1);
}
