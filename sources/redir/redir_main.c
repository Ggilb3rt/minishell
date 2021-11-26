/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alangloi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 14:35:46 by alangloi          #+#    #+#             */
/*   Updated: 2021/11/26 14:35:47 by alangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redir_less(t_split *split, t_command **cur, t_list_envp *ms_env)
{
	split->red = 0;
	split->i++;
	del_spaces(split);
	(*cur)->in_file = malloc(sizeof(char) * (ret_val(split, ms_env) + 1));
	split->open_d = 0;
	split->open_s = 0;
	while (split->str[split->i])
	{
		if (!get_string(split, ms_env, cur, 3))
			break ;
	}
	(*cur)->token_in = LESS;
	(*cur)->token_out = 0;
	(*cur)->in_file[split->red] = '\0';
}

static void	redir_great(t_split *split, t_command **cur, t_list_envp *ms_env)
{
	split->red = 0;
	split->i++;
	del_spaces(split);
	(*cur)->out_file = malloc(sizeof(char) * (ret_val(split, ms_env) + 1));
	split->open_d = 0;
	split->open_s = 0;
	while (split->str[split->i])
	{
		if (!get_string(split, ms_env, cur, 2))
			break ;
	}
	(*cur)->token_in = 0;
	(*cur)->token_out = GREAT;
	(*cur)->out_file[split->red] = '\0';
}

static void	redir_dgreat(t_split *split, t_command **cur, t_list_envp *ms_env)
{
	split->red = 0;
	split->i += 2;
	del_spaces(split);
	(*cur)->out_file = malloc(sizeof(char) * (ret_val(split, ms_env) + 1));
	split->open_d = 0;
	split->open_s = 0;
	while (split->str[split->i])
	{
		if (!get_string(split, ms_env, cur, 2))
			break ;
	}
	(*cur)->token_in = 0;
	(*cur)->token_out = DGREAT;
	(*cur)->out_file[split->red] = '\0';
}

static void	redir_dless(t_split *split, t_command **cur)
{
	int	i;

	i = 0;
	split->i += 2;
	del_spaces(split);
	(*cur)->end = malloc(sizeof(char) * (ret_val(split, NULL) + 1));
	while (split->str[split->i] && split->str[split->i] != ' ')
	{
		(*cur)->end[i] = split->str[split->i];
		split->i++;
		i++;
	}
	(*cur)->token_in = DLESS;
	(*cur)->token_out = 0;
	(*cur)->end[i] = '\0';
	g_ret.ret = EHERE;
}

void	redirection(t_split *split, t_command **cur, t_list_envp *ms_env)
{
	if (split->str[split->i] == '<' && split->str[split->i + 1] != '<')
		redir_less(split, cur, ms_env);
	else if (split->str[split->i] == '>' && split->str[split->i + 1] != '>')
		redir_great(split, cur, ms_env);
	else if (split->str[split->i] == '>' && split->str[split->i + 1] == '>')
		redir_dgreat(split, cur, ms_env);
	else if (split->str[split->i] == '<' && split->str[split->i + 1] == '<')
		redir_dless(split, cur);
}
