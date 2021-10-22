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

static void init_cmd(t_command *cmd)
{
	cmd->numb_avail_simple_commands = 0;
	cmd->numb_simple_commands = 0;
	cmd->list = NULL;
	cmd->out_file = ms_strdup("dflt");
	cmd->in_file = ms_strdup("dflt");
	cmd->err_file = ms_strdup("dflt");
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
	g_sig.ret = 1;
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
			exit(0);
		}
		if (g_sig.ret == 2) {
			rl_on_new_line();
			printf("yooylo\n");
		}
		g_sig.ret = cmd_exit(line);
		add_history(line);
		//print_simple_command(cmd->list);
	}
	free(msg_prompt);
	ms_lst_free_all(ms_envp);
	return (1);
}
