#include "minishell.h"

/* create the loop that will run minishell
 */

int	main(int ac, char **av, char **env)
{
	char	*line;

	(void)ac;
	(void)av;
	while (1)
	{
		line = readline("user@root > ");
		if (!parse_line(line))
			break ;
		add_history(line);
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
	}
	return (1);
}
