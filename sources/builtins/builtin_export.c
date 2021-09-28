//
// Created by Antoine LANGLOIS on 22/09/2021.
//

#include "minishell.h"

/* export with no options : export 'name'='word'
 * - Set export attribute for shell variables, corresponding to the specified 'name', which shall cause them to
 * be in the environment of subsequently executed builtins. If the name of a variable is followed by ='word', then
 * the value of that variable shall be set to 'word'.
 * The shell shall format the ouptut, including the proper use of quoting, so that it is suitable for reinput to the
 * shell as builtins that achieve the same exporting results.
 */

/* things we need to know :
 * ' inhibit all interpretation of a sequence of characters.
 * " inhibit all interpretation of a sequence of characters except for $.
 */

int 		cmd_export(void)
{
	printf("USE OF THE EXPORT COMMAND\n");
	return (1);
}