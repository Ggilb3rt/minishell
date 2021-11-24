//
// Created by alangloi on 11/24/21.
//

#include "minishell.h"

void	get_char(t_split *split)
{
	split->new[split->o][split->l] = split->str[split->i];
	split->l++;
	split->i++;
}

void get_arg(t_split *split, t_command *cur, t_command **cmd)
{
	printf("\ttata\n");
	split->new[split->o][split->l] = '\0';
	printf("\ttati\n");
	split->new[split->o + 1] = NULL;
	printf("\ttato\n");
	cur->arg = split->new;
	printf("\ttatu\n");
	cur->token = create_token(cur->arg[0]);
	printf("\ttate\n");
	add_command(cur, cmd);
	cur = NULL;
}

int get_arg_pipe(t_split *split, t_command *cur, t_command **cmd)
{
	split->i++;
	del_spaces(split);
	if (!split->str[split->i])
		return (0);
	get_arg(split, cur, cmd);
	return (1);
}

int get_word_space(t_split *split, t_list_envp *ms_env)
{
	split->i++;
	del_spaces(split);
	split->new[split->o][split->l] = '\0';
	split->l = 0;
	if (split->str[split->i] == '|')
		return (1);
	if (!split->str[split->i])
		return (0);
	if (split->str[split->i] == '>' || split->str[split->i] == '<')
		return (0);
	split->o++;
	if (!alloc_word(split, ms_env))
		return (0);
	return (1);
}