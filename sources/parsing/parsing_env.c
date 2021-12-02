/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 14:34:30 by alangloi          #+#    #+#             */
/*   Updated: 2021/12/02 07:46:37 by ggilbert         ###   ########.fr       */
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
		{
			split->new[split->o][split->l] = arg[split->q];
			split->l++;
		}
		else if (print == 2)
		{
			(*cur)->out_file[split->red] = arg[split->q];
			split->red++;
		}
		else if (print == 3)
		{
			(*cur)->in_file[split->red] = arg[split->q];
			split->red++;
		}
		else if (print == 4)
		{
			(*cur)->end[split->red] = arg[split->q];
			split->red++;
		}
		split->q++;
	}
}

static int	return_value(t_split *split, int print, t_command **cur)
{
	char	*arg;

	if (split->str[split->i + 1] == '?')
	{
		split->i += 2;
		arg = ft_itoa(g_ret.ret);
		print_var(split, print, cur, arg);
		free(arg);
		arg = NULL;
		return (0);
	}
	else if (split->str[split->i + 1] == '0')
	{
		split->i += 2;
		arg = ft_strdup("minishell");
		print_var(split, print, cur, arg);
		free(arg);
		arg = NULL;
		return (0);
	}
	return (1);
}

static void	handle_var(t_split *split, int print,
						t_list_envp *ms_env, t_command **cur)
{
	char	*var;
	char	*arg;

	var = assign_var(split);
	arg = cur[0]->arg[0];
	if (var)
	{
		arg = get_ms_env_val(var, ms_env);
		if (!arg)
			arg = ft_strdup("\0");
		print_var(split, print, cur, arg);
		free(var);
		var = NULL;
	}
	free(arg);
	arg = NULL;
}

int	search_var(t_split *split, t_list_envp *ms_env,
				int print, t_command **cur)
{
	if (split->str[split->i] == '$')
	{
		if (split->str[split->i + 1] == ' ')
			return (0);
		if (!return_value(split, print, cur))
			return (1);
		if (ft_isdigit(split->str[split->i + 1]))
		{
			split->i += 2;
			return (0);
		}
		handle_var(split, print, ms_env, cur);
		return (1);
	}
	else
		return (0);
}
