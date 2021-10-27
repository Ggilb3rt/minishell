//
// Created by Antoine LANGLOIS on 27/10/2021.
//

#include "minishell.h"

void 	heredoc_func(char *arg, t_command **cmd, int *g_ret)
{
	char *msg_prompt;
	char *line;

	(void)arg;
	printf("HEREDOC EOF = %s, FILE = %s\n", (*cmd)->heredoc, (*cmd)->out_file);
	msg_prompt = strdup("heredoc> ");
	while (g_ret)
	{
		line = readline(msg_prompt);
		printf("\tline=%s\n", line);
		if (!ms_strcmp(line, (*cmd)->heredoc))
		{
			execve("/bin/cat", &(*cmd)->out_file, NULL);
			*g_ret = 0;
			printf("bye\n");
			cmd_exit(line);
			//exit(0);
		}
	}
}