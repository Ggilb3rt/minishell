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

int    cmd_exit(void)
{
	printf("USE OF THE EXIT COMMAND\n");
	return (0);
}