//
// Created by antoine on 26/11/2021.
//

#include "minishell.h"

static void get_redir(t_split *split, int print, t_command **cur)
{
	if (print == 2)
		(*cur)->out_file[split->red] = split->str[split->i];
	else if (print == 3)
		(*cur)->in_file[split->red] = split->str[split->i];
	split->i++;
	split->red++;
}

void get_string(t_split *split, t_list_envp *ms_env, t_command **cur, int print)
{
	if (open_quote(split))
	{
		while (close_quote(split))
		{
			if (!split->open_s && split->open_d)
			{
				if (!search_var(split, ms_env, print, cur))
					get_redir(split, print, cur);
			}
			else
				get_redir(split, print, cur);
		}
	}
	else if (!search_var(split, ms_env, print, cur))
		get_redir(split, print, cur);
}