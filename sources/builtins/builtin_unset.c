//
// Created by Antoine LANGLOIS on 22/09/2021.
//

#include "minishell.h"

/* unset with no options or arguments : unset 'name'
 * - Unset values and attributes of variables and functions
 * each variable of function specified by name shall be unset.
 * Unsetting a variable or function that was not previously set shall not be considered an error and does not
 * cause the shell to abort.
 * NOTE : VARIABLE= is equivalent to VARIABLE=""
 */

/*

get identifier
check in lst if identifier exist
if exist remove
remove() =>
	get previous item->next
	get next item adress
	free content
	free current item
	pointer from previous item to next item

void		ms_lst_pop_inside(t_list_envp *current, t_list_envp *prev)
t_list_envp	*ms_lst_point(int index, t_list_envp *ms_env)



*/

int	cmd_unset(void)
{
	printf("USE OF THE UNSED COMMAND\n");
	return (1);
}
