#include "minishell.h"

/* create the loop that will run minishell
 */

int	main(int ac, char **av, char **env)
{
	char		*line;
	t_ms_envp	ms_envp;

	(void)ac;
	(void)av;
	ms_envp = init_ms_envp(env);
	while (1)
	{
		line = readline("user@root > ");
		if (!parse_line(line))
			break ;
		add_history(line);
	}
	return (1);
}
