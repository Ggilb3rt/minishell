//
// Created by Antoine LANGLOIS on 22/09/2021.
//

#include "minishell.h"

/* exit with no options : exit 'n'
 * - cause the shell to exit from its current execution environment with the exit status specified by the
 * unsigned decimal integer 'n'. If the current execution environment is a subshell environment, the shell
 * shall exit from the subshell environment with the specified exit status and continue in the environment from
 * which that subshell environment was invoked;
 * otherwise, the shell utility shall terminate with the specified exit status. If 'n' is specified, but its
 * value is not between 0 and 255 inclusively, the exit status is undefined
 */

/* the exit command should interrupt the prompt if "exit" is typen or if CTRL-D is pressed
 * in the case if CTRL-D is pressed, refer to a specific function stored with the other functions
 * involving key pressed (CTRL-C, CTRL-\)
 */


/*
Exemples de tests

bash> exit				==> 0
bash> exit 42			==> 42
bash> exit 256			==> 0
bash> exit -42			==> 214
bash> exit a 42			==> exit + err numeric arg required + return 255
bash> exit 42 a			==> no exit + err too many arg + return 1
bash> exit a			==> exit + err numeric arg required + return 255
bash> exit a a			==> == exit a 42
bash> exit 28374623874627346234629423423 ==> == exit a 42
bash> exit | exit		==> do nothing + return 0
bash> exit 42 | exit -42	==> do nothing + return 214


le retour de exit est toujour compris entre 0 et 255
*/

int	cmd_exit(char *line)
{
	if (!line)
		return (0);
	if (!ft_strcmp(line, "exit"))
	{
		printf("exit\n");
		return (1);
	}
	return (0);
}
