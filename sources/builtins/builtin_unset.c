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
if exist && != head
	ms_lst_pop_inside()
else
	ms_env = ms_lst_pop_first()

void		ms_lst_pop_inside(t_list_envp *current, t_list_envp *prev)
t_list_envp	*ms_lst_point(int index, t_list_envp *ms_env)
t_list_envp	*ms_lst_pop_first(t_list_envp *head)


need to add error msg : minishell: unset: `@sfd': not a valid identifier
*/

void	remove_first_or_inside(t_list_envp **env, int current_index)
{
	if (current_index == 0)
	{
		printf("\n%p\n", *env);
		*env = ms_lst_pop_first(*env);
		printf("%p\n\n", *env);
	}
	else
	{
		ms_lst_pop_inside(
			ms_lst_point(current_index, *env),
			ms_lst_point(current_index - 1, *env));
	}
}

int	cmd_unset(t_list_envp **env, char **to_find)
{
	int	current_index;
	int	i;

	if (!env || !to_find)
		return (1);
	i = 0;
	while (to_find[i] != NULL)
	{
		if (!ms_str_isalnum_under(to_find[i]))
		{
			printf("minishell: unset: `%s': not a valid identifier\n",
				to_find[i]);
			break ;
		}
		current_index = get_ms_env_index(to_find[i], *env);
		if (current_index == -1)
			break ;
		remove_first_or_inside(env, current_index);
		i++;
	}
	return (0);
}
