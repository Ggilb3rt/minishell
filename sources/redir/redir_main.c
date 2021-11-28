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

static int	redir_great(t_split *split, t_command **cur, t_list_envp *ms_env)
{
	split->red = 0;
	split->i++;
	del_spaces(split);
	if (split->str[split->i] == '|')
	{
		printf("minishell: syntax error near unexpected token '|'\n");
		return (-1);
	}
	if (!split->str[split->i])
	{
		printf("bash: syntax error near unexpected token `newline'\n");
		return (-1);
	}
	(*cur)->out_file = malloc(sizeof(char) * (ret_val(split, ms_env, 0) + 1));
	if (!(*cur)->out_file)
		return (0);
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
	init_out_file_fd((*cur)->token_out, (*cur)->out_file, &(*cur)->fd_out);
	return (1);
}

static int	redir_dgreat(t_split *split, t_command **cur, t_list_envp *ms_env)
{
	split->red = 0;
	split->i += 2;
	del_spaces(split);
	if (split->str[split->i] == '|')
	{
		printf("minishell: syntax error near unexpected token '|'\n");
		return (-1);
	}
	if (!split->str[split->i])
	{
		printf("bash: syntax error near unexpected token `newline'\n");
		return (-1);
	}
	(*cur)->out_file = malloc(sizeof(char) * (ret_val(split, ms_env, 0) + 1));
	if (!(*cur)->out_file)
		return (0);
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
	init_out_file_fd((*cur)->token_out, (*cur)->out_file, &(*cur)->fd_out);
	return (1);
}

static int	redir_less(t_split *split, t_command **cur, t_list_envp *ms_env)
{
	split->red = 0;
	split->i++;
	del_spaces(split);
	if (split->str[split->i] == '|')
	{
		printf("minishell: syntax error near unexpected token '|'\n");
		return (-1);
	}
	if (!split->str[split->i])
	{
		printf("bash: syntax error near unexpected token `newline'\n");
		return (-1);
	}
	(*cur)->in_file = malloc(sizeof(char) * (ret_val(split, ms_env, 0) + 1));
	if (!(*cur)->in_file)
		return (0);
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
	init_in_file_fd((*cur)->token_in, (*cur)->in_file, &(*cur)->fd_in);
	return (1);
}

static int	redir_dless(t_split *split, t_command **cur, t_list_envp *ms_env)
{
	split->red = 0;
	split->i += 2;
	del_spaces(split);
	if (split->str[split->i] == '|')
	{
		printf("minishell: syntax error near unexpected token '|'\n");
		return (-1);
	}
	if (!split->str[split->i])
	{
		printf("bash: syntax error near unexpected token `newline'\n");
		return (-1);
	}
	(*cur)->end = malloc(sizeof(char) * (ret_val(split, ms_env, 1) + 1));
	if (!(*cur)->end)
		return (0);
	split->open_d = 0;
	split->open_s = 0;
	while (split->str[split->i] && split->str[split->i] != ' ')
	{
		if (!get_string(split, ms_env, cur, 4))
			break ;
	}
	(*cur)->token_in = DLESS;
	(*cur)->token_out = 0;
	(*cur)->end[split->red] = '\0';
	g_ret.ret = EHERE;
	init_in_file_fd((*cur)->token_in, (*cur)->in_file, &(*cur)->fd_in);
	return (1);
}

int	redirection(t_split *split, t_command **cur, t_list_envp *ms_env)
{
	int	ret;

	if (split->str[split->i] == '>' && split->str[split->i + 1] != '>')
		ret = redir_great(split, cur, ms_env);
	else if (split->str[split->i] == '>' && split->str[split->i + 1] == '>')
		ret = redir_dgreat(split, cur, ms_env);
	else if (split->str[split->i] == '<' && split->str[split->i + 1] != '<')
		ret = redir_less(split, cur, ms_env);
	else if (split->str[split->i] == '<' && split->str[split->i + 1] == '<')
		ret = redir_dless(split, cur, ms_env);
	if (split->str[split->i] == ' ')
	{
		if (!get_word_space(split, ms_env))
			return (0);
	}
	return (ret);
}
