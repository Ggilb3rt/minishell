#include "minishell.h"

/* create the loop that will run minishell
 */

/*
 * username = getenv("USER")
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

int	main(int ac, char **av, char **env)
{
	char *line;
	t_command *cmd;

	(void) ac;
	(void) av;
	(void) env;
	cmd = malloc(sizeof(t_command));
	init_cmd(cmd);
	while (1)
	{
		line = readline("user@root > ");
		if (!lexer_and_parser(line, cmd))
			break;
		add_history(line);
	}
	return (1);
}

/*
		printf("\ntests cd echo pwd\n");
		cmd_pwd();
		cmd_echo("-n");
		cmd_cd("tests/no_perm", env);
		cmd_cd("sldfkh", env);
		cmd_cd("../", env);
		cmd_pwd();
		cmd_cd("~", env);
		cmd_cd("/", env);
		cmd_pwd();
		cmd_cd("-sdf", env);	//err
		cmd_pwd();
		cmd_cd("-pwd", env);	//err
		cmd_pwd();
		cmd_cd("- ", env);		// work
		cmd_pwd();
		cmd_cd("-pouet", env);		// err
		cmd_pwd();
		cmd_cd("-", env);		// work // segfault
		cmd_pwd();
		cmd_cd("-   sdf", env);	// work
		cmd_pwd();
*/