/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_ret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alangloi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 14:36:07 by alangloi          #+#    #+#             */
/*   Updated: 2021/11/26 14:36:10 by alangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	stock_var(t_split *split, t_redir *redir)
{
	redir->l++;
	redir->k = redir->l + redir->i;
	while (parse_var(split->str[redir->l + redir->i]))
		redir->l++;
	redir->var = ft_substr(split->str, redir->k,
			redir->l + redir->i - redir->k);
}

static void	ret_open_double(t_split *split, t_redir *redir)
{
	split->open_d = 1;
	redir->l++;
	while (split->str[redir->i + redir->l] != '\"'
		&& !split->open_s && split->open_d)
	{
		redir->i++;
		if (!split->open_s && split->open_d)
		{
			if (split->str[redir->i + redir->l] == '$')
				stock_var(split, redir);
		}
		if (split->str[redir->i + redir->l] == '\"'
			&& !split->open_s && split->open_d)
		{
			split->open_d = 0;
			redir->l++;
		}
	}
}

static void	ret_open_simple(t_split *split, t_redir *redir)
{
	split->open_s = 1;
	redir->l++;
	while (split->str[redir->i + redir->l] != '\''
		&& !split->open_d && split->open_s)
	{
		redir->i++;
		if (split->str[redir->i + redir->l] == '\''
			&& !split->open_s && split->open_d)
		{
			split->open_s = 0;
			redir->l++;
		}
	}
}

static void	check_ret(t_split *split, t_redir *redir)
{
	if (split->str[redir->i + redir->l] == '\"'
		&& !split->open_s && !split->open_d)
		ret_open_double(split, redir);
	else if (split->str[redir->i + redir->l] == '\''
		&& !split->open_d && !split->open_s)
		ret_open_simple(split, redir);
	else if (split->str[redir->i + redir->l] == '$')
		stock_var(split, redir);
	else
		redir->i++;
}

int	ret_val(t_split *split, t_list_envp *ms_env)
{
	t_redir	redir;

	redir.i = 0;
	redir.l = split->i;
	redir.var = NULL;
	split->open_d = 0;
	split->open_s = 0;
	while (split->str[redir.i + redir.l]
		&& split->str[redir.i + redir.l] != ' ')
		check_ret(split, &redir);
	if (redir.var)
		redir.i += (int)ft_strlen(get_ms_env_val(redir.var, ms_env));
	return (redir.i);
}
