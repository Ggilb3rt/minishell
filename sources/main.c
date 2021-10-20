#include "minishell.h"

/* create the loop that will run minishell
 */

/*

*Utiliser la lst et creer a partir d'elle un char ** temporaire
*qui sera utilise uniquement pour execve
+ en parti fonctionnel
- il faut creer la fonction du char ** temporaire
+ l'ajout de var est moins gourement en ressources
- beaucoup de traitement pour peu de choses, beaucoup de doublons de contenu

*Ou mettre a jour envp ?
- puis-je mettre a jour envp ?
- l'ajout d'une var demande de recreer le char **
+ mise en place plus simple a mon gout

free envp n'est pas possible,
il faudra recreer un char ** quoi qu'il arrive
autant garder la lst et creer un char ** temporaire pour execve
j'ai deja creer mon propre getenv()
*/



int	main(int ac, char **av, char **envp)
{
	t_list_envp	*ms_envp;
	//char		*line;
	//char		*msg_prompt;

	(void)ac;
	(void)av;
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
	/*msg_prompt = ms_strjoin(get_ms_env_val(USER, ms_envp), "@minishell > ");
	while (1)
	{
		line = readline(msg_prompt);
		if (!parse_line(line))
			break ;
		add_history(line);
	}
	free(msg_prompt);
	*/
	ms_lst_free_all(ms_envp);
	//free_tab(env);
	return (0); // return 0 or 1 ?
}
