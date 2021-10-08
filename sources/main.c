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

	(void)ac;
	(void)av;
	ms_envp = create_msenvp_lst(envp);

	char	**export = ms_split("POUET=lol err BIP=Boup PWD=/ PLOP=plop POUET=bip", ' ');
	cmd_export(ms_envp, export);
	cmd_env(ms_envp);
	free_tab(export);

	char **pouet;
	pouet = ms_split("TERM_PROGRAM PLOP POUET @sdf PWD ROBERT TERM", ' ');
	cmd_unset(&ms_envp, pouet);
	free_tab(pouet);
	pouet = NULL;

	printf("%p\n\n\n", ms_envp);
	cmd_env(ms_envp);

	printf("\nChar ** point to lst (need with execve)\n\n");
	char **pouet2 = convert_envplst_to_tab(ms_envp);
	printf("Pouet : %p | %p\n", pouet2, ms_envp);
	int	i = 0;
	while (pouet2[i] != NULL)
		printf("char **%s\n", pouet2[i++]);
	//free(pouet2);
	/*while (1)
	{
		line = readline("user@root > ");
		if (!parse_line(line))
			break ;
		add_history(line);
	}*/
	ms_lst_free_all(ms_envp);
	return (1);
}
