#include "minishell.h"

/* create the loop that will run minishell
 */

int	main(void)
{
	char	*line;

	while (1)
	{
		line = readline("user@root > ");
		if (!parse_line(line))
			break ;
		add_history(line);
		cmd_pwd();
		cmd_echo("-n");
	}
	return (1);
}
