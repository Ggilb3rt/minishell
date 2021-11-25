//
// Created by alangloi on 11/24/21.
//

#include "minishell.h"

static char	*assign_var(t_split *split)
{
	char	*var;
	int		k;

	split->i++;
	k = split->i;
	var = NULL;
	while (split->str[split->i] != ' ' && split->str[split->i] != '\0' && split->str[split->i] != '\'' && split->str[split->i] != '\"')
		split->i++;
	var = ft_substr(split->str, k, split->i - k);
	if (var)
		return (var);
	return (NULL);
}

int	search_var(t_split *split, t_list_envp *ms_env, int print)
{
	char *var;
	char *arg;

	if (split->str[split->i] == '$')
	{
		var = assign_var(split);
		if (var)
		{
			arg = get_ms_env_val(var, ms_env);
			if (!arg)
				arg = ft_strdup("");
			split->q = 0;
			while (arg[split->q])
			{
				if (print == 1)
					split->new[split->o][split->l] = arg[split->q];
				split->l++;
				split->q++;
			}
		}
		return (1);
	}
	else
		return (0);
}