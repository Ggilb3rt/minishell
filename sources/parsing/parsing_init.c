//
// Created by alangloi on 11/24/21.
//

#include "minishell.h"

void	init_split(t_split *split, char *str)
{
	(void)str;
	split->str = str;
	split->i = 0;
	split->l = 0;
	split->o = 0;
	split->q = 0;
	split->open_s = 0;
	split->open_d = 0;
}

int init_arg(t_split *split, t_command *cur, t_list_envp *ms_env)
{
	split->o = 0;
	split->l = 0;
	if (!alloc_arg(split))
		return (0);
	if (!alloc_word(split, ms_env))
		return (0);
	cur = alloc_command(NULL);
	if (!cur)
		return (0);
	return (1);
}