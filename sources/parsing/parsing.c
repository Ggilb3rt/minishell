//
// Created by Antoine LANGLOIS on 22/09/2021.
//

#include "parsing.h"

/* theses functions will parse the string entered in the prompt
 * they will store all the information we need in a structure declared in the associated header file
 *
 * what we need to know :
 * - the subject specifies that we don't need to interpret unclosed quotes or unspecified special
 * characters
 */


static int 	launch_command(char *str)
{
	if (!ms_strcmp(str, "echo"))
		return (cmd_echo());
	if (!ms_strcmp(str, "cd"))
		return (cmd_cd());
	if (!ms_strcmp(str, "pwd"))
		return (cmd_pwd());
	if (!ms_strcmp(str, "export"))
		return (cmd_export());
	if (!ms_strcmp(str, "unset"))
		return (cmd_unset());
	if (!ms_strcmp(str, "env"))
		return (cmd_env());
	if (!ms_strcmp(str, "exit"))
		return (cmd_exit());
	return (1);
}

static void process_com(char *str)
{
	if (!ms_strcmp(str, ">"))
		flux_redir_output();
	if (!ms_strcmp(str, "<"))
		flux_redir_input();
	if (!ms_strcmp(str, ">>"))
		flux_append();
	if (!ms_strcmp(str, "<<"))
		flux_heredoc();
	if (!ms_strcmp(str, "|"))
		flux_pipe();
}

int		parse_line(char *str)
{
	char **arr;
	int	arr_nb;
	int i;

	i = 0;
	arr = ms_split(str, ' ');
	arr_nb = array_count(arr);
	printf("number of tabs : %d\n", arr_nb);
	while (arr[i])
	{
		if (launch_command(arr[i]) == 0)
			return (0);
		process_com(arr[i]);
		i++;
	}
	return (1);
}