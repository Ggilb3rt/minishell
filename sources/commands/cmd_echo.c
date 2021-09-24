//
// Created by Antoine LANGLOIS on 22/09/2021.
//

#include "commands.h"

/* echo with option -n : echo 'string'
 * - echo writes the string entered as an argument on the standard output
 * the option -n don't output the trailing newline
 */

int		cmd_echo(void)
{
	printf("USE OF THE ECHO COMMAND\n");
	return (1);
}