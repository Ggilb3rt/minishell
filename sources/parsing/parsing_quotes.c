//
// Created by alangloi on 11/24/21.
//
#include "minishell.h"

int	open_quote(t_split *split)
{
	if (split->str[split->i] == '\"' && !split->open_s && !split->open_d)
	{
		split->open_d = 1;
		split->i++;
		return (1);
	}
	if (split->str[split->i] == '\'' && !split->open_d && !split->open_s)
	{
		split->open_s = 1;
		split->i++;
		return (1);
	}
	return (0);
}

int	close_quote(t_split *split)
{
	if (split->str[split->i] == '\"' && !split->open_s && split->open_d)
	{
		split->open_d = 0;
		split->i++;
		return (0);
	}
	if (split->str[split->i] == '\'' && !split->open_d && split->open_s)
	{
		split->open_s = 0;
		split->i++;
		return (0);
	}
	return (1);
}

void into_quote(t_split *split, t_list_envp *ms_env)
{
	while (close_quote(split))
	{
		if (!split->open_s && split->open_d)
		{
			if (!search_var(split, ms_env))
				get_char(split);
		}
		else
			get_char(split);
	}
}