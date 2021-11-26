/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alangloi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 14:34:30 by alangloi          #+#    #+#             */
/*   Updated: 2021/11/26 14:34:33 by alangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*assign_var(t_split *split)
{
	char	*var;
	int		k;

	split->i++;
	k = split->i;
	var = NULL;
	while (parse_var(split->str[split->i]))
		split->i++;
	var = ft_substr(split->str, k, split->i - k);
	if (var)
		return (var);
	return (NULL);
}

static void	print_var(t_split *split, int print,
						t_command **cur, const char *arg)
{
	split->q = 0;
	while (arg[split->q])
	{
		if (print == 1)
			split->new[split->o][split->l] = arg[split->q];
		else if (print == 2)
			(*cur)->out_file[split->red] = arg[split->q];
		else if (print == 3)
			(*cur)->in_file[split->red] = arg[split->q];
		else if (print == 4)
			(*cur)->end[split->red] = arg[split->q];
		split->l++;
		split->q++;
		split->red++;
	}
}

int	search_var(t_split *split, t_list_envp *ms_env,
				int print, t_command **cur)
{
	char	*var;
	char	*arg;

	(void)cur;
	if (split->str[split->i] == '$')
	{
		if (split->str[split->i + 1] == '?')
		{
			split->i += 2;
			arg = ft_itoa(g_ret.ret);
			print_var(split, print, cur, arg);
			free(arg);
			return (1);
		}
		var = assign_var(split);
		if (var)
		{
			arg = get_ms_env_val(var, ms_env);
			if (!arg)
				arg = ft_strdup("");
			print_var(split, print, cur, arg);
		}
		free(var);
		free(arg);
		return (1);
	}
	else
		return (0);
}
