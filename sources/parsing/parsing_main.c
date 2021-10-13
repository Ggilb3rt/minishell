//
// Created by Antoine LANGLOIS on 22/09/2021.
//

#include "minishell.h"

/* these functions will parse the string entered in the prompt
 * they will store all the information we need in a structure declared in the associated header file
 *
 * what we need to know :
 * - the subject specifies that we don't need to interpret unclosed quotes or unspecified special
 * characters
 */

/*
 * convert argument into token, here we have a little problem because when removing the first allocation (ERROR) of
 * new[i], the first value of the array gives a strange output. Problem to solve
 */

int		lexer_and_parser(char *str, t_command *cmd)
{
	char		**arg;
	//int 		ret;

	(void)cmd;
	arg = split_quote(str);
	int i = 0;
	while(arg[i]) {
		printf("\t|%s|\n", arg[i]);
		i++;
	}
	/*
	cmd->list = lexer(arg);
	if (!cmd->list)
	{
		printf("Error input string\n");
		exit (0);
	}
	ret = parser(cmd);
	if (!ret)
	{
		printf("Error synthax\n");
		exit (0);
	}
	 */
	return (1);
}