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
void	put_err(char *str)
{
	write(STDERR_FILENO, str, ms_strlen(str));
}

void	close_unneeded(unsigned int *c, int *from, int *to)
{
	if (*c == UINT_MAX)
		*c = 2;
	if (*c % 2 == 1)
	{
		close(from[0]);
		close(from[1]);
		close(to[0]);
	}
	else
	{
		close(to[0]);
		close(to[1]);
		close(from[1]);
	}
}

pid_t	exec_from_to(int from[2], int to[2], char **cmd, char **envp)
{
	pid_t				pid;
	static unsigned int	count = 1;

	pid = fork();
	if (pid == 0)
	{
		dup2(from[0], STDIN_FILENO);
		dup2(to[1], STDOUT_FILENO);
		close_unneeded(&count, from, to);
		count++;
		execve(cmd[0], cmd, envp);
		if (errno == 2)
		{
			put_err(cmd[0]);
			put_err(": command not found\n");
			exit(EXIT_FAILURE);
		}
		else
		{
			perror(cmd[0]);
			exit(EXIT_FAILURE);
		}
	}
	return (pid);
}


int	main(int ac, char **av, char **envp)
{
	t_list_envp	*ms_envp;
	int			fd_pipe[2];
	int			fd_file[2];
	pid_t		pid[3];
	//char		*line;
	//char		*msg_prompt;

	(void)ac;
	(void)av;
	ms_envp = create_msenvp_lst(envp);


	// ls -la | grep sep | grep drw > pouet
	//int	fd_std[2] = {0, 1};
	char **env = convert_envplst_to_tab(ms_envp);
	char **cmd1 = ms_split("ls -la", ' ');
	char **cmd2 = ms_split("ls -l", ' ');
	//char **cmd3 = ms_split("grep sep", ' ');
	cmd1[0] = init_cmd_path(cmd1[0], get_ms_env_val(PATH, ms_envp));
	cmd2[0] = init_cmd_path(cmd2[0], get_ms_env_val(PATH, ms_envp));
	//cmd3[0] = init_cmd_path(cmd3[0], get_ms_env_val(PATH, ms_envp));
	printf("CMD1 = \"%s\"\n", cmd1[0]);
	pipe(fd_pipe);
	printf("pipe fds %d %d\n", fd_pipe[0], fd_pipe[1]);
	fd_file[0] = -1;
	fd_file[1] = open("./pouet", O_WRONLY | O_TRUNC | O_CREAT, 0666);
	printf("files fds %d %d\n", fd_file[0], fd_file[1]);
	pid[0] = exec_from_to(fd_pipe, fd_pipe, cmd1, env);
	printf("pid[0]\n");
	pid[1] = exec_from_to(fd_pipe, fd_pipe, cmd2, env);
	printf("pid[1]\n");
	//pid[2] = exec_from_to(fd_pipe, fd_file, cmd3, env);
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	close(fd_file[1]);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
	//waitpid(pid[2], NULL, 0);
	//pipes_fds = create_pipes_fd(5);
	/*int	**pipes;
	pipes = malloc(sizeof(int *) * 5);
	for (int i = 0; i < 5; i++)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		pipe(pipes[i]);
		printf("pipe[%d] fd read = %d | write = %d\n", i, pipes[i][0], pipes[i][1]);
	}*/



	/*
	char **cmd = ms_split("/bin/ls -l", ' ');
	cmd[0] = init_cmd_path(cmd[0], get_ms_env_val(PATH, ms_envp));
	printf("pouet %s\n", cmd[0]);
	int ret = execve(cmd[0], cmd, convert_envplst_to_tab(ms_envp));
	printf("%d\n", ret);
	strerror(errno);
	*/
	/*msg_prompt = ms_strjoin(get_ms_env_val(USER, ms_envp), "@minishell > ");
	while (1)
	{
		line = readline(msg_prompt);
		if (!parse_line(line))
			break ;
		add_history(line);
	}
	free(msg_prompt);*/
	ms_lst_free_all(ms_envp);
	return (1);
}
