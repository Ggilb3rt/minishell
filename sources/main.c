#include "minishell.h"

/* create the loop that will run minishell
 */

int	main(int ac, char **av, char **envp)
{
	char		*line;
	t_list_envp	*ms_envp;
	//char		*env_line;

	(void)ac;
	(void)av;
	//(void)envp;
	ms_envp = create_msenvp_lst(envp);
	/*env_line = get_ms_env_val("sdfkjh", ms_envp);
	printf("1.envline : %s\n", env_line);
	env_line = get_ms_env_val("PWD", ms_envp);
	printf("2.envline : %s\n\n", env_line);
	cmd_pwd();
	cmd_cd("../", ms_envp, envp);
	cmd_pwd();
	env_line = get_ms_env_val("PWD", ms_envp);
	printf("3.envline : %s\nNEWPWD %s\n", env_line,
			get_env_val("PWD", envp));*/
	cmd_pwd(get_ms_env_val("PWD", ms_envp), 1);
	//cmd_env(ms_envp);
	printf("NEWPDW %s |%p\n", get_ms_env_val("PWD", ms_envp), get_ms_env_val("PWD", ms_envp));
	while (1)
	{
		line = readline("user@root > ");
		if (!parse_line(line))
			break ;
		add_history(line);
	}
	ms_lst_free_all(ms_envp);
	return (1);
}
