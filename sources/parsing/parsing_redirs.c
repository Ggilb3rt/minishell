//
// Created by alangloi on 11/24/21.
//

#include "minishell.h"

static void redir_less(t_split *split, t_command **cur, t_list_envp *ms_env)
{
	int i;

	i = 0;
	(void)ms_env;
	split->i++;
	del_spaces(split);
	(*cur)->in_file = malloc(sizeof(char) * (ret_val(split, ms_env) + 1));
	while (split->str[split->i] && split->str[split->i] != ' ')
	{
		(*cur)->in_file[i] = split->str[split->i];
		split->i++;
		i++;
	}
	(*cur)->token_in = LESS;
	(*cur)->token_out = 0;
	(*cur)->in_file[i] = '\0';
}

static void redir_great(t_split *split, t_command **cur, t_list_envp *ms_env)
{
	int i;

	i = 0;
	(void)ms_env;
	split->i++;
	del_spaces(split);
	(*cur)->out_file = malloc(sizeof(char) * (ret_val(split, ms_env) + 1));
	while (split->str[split->i] && split->str[split->i] != ' ')
	{
		(*cur)->out_file[i] = split->str[split->i];
		split->i++;
		i++;
	}
	(*cur)->token_in = 0;
	(*cur)->token_out = GREAT;
	(*cur)->out_file[i] = '\0';
}

static void redir_dgreat(t_split *split, t_command **cur, t_list_envp *ms_env)
{
	int i;

	i = 0;
	(void)ms_env;
	split->i += 2;
	del_spaces(split);
	(*cur)->out_file = malloc(sizeof(char) * (ret_val(split, ms_env) + 1));
	while (split->str[split->i] && split->str[split->i] != ' ')
	{
		(*cur)->out_file[i] = split->str[split->i];
		split->i++;
		i++;
	}
	(*cur)->token_in = 0;
	(*cur)->token_out = DGREAT;
	(*cur)->out_file[i] = '\0';
}

static void redir_dless(t_split *split, t_command **cur)
{
	int i;

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