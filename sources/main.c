#include "minishell.h"

/* create the loop that will run minishell
 */

int	main(int ac, char **av, char **envp)
{
	char		*line;

	(void)ac;
	(void)av;
	(void)envp;
	envp_test();
	while (1)
	{
		line = readline("user@root > ");
		if (!parse_line(line))
			break ;
		add_history(line);
	}
	return (1);
}
