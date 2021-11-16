//
// Created by antoine on 15/11/2021.
//

#include "minishell.h"

static char *assign_var(char *str, int j)
{
	int k;
	char *var;

	k = 0;
	var = NULL;
	while (str[j + k] != ' ' && str[j + k] != '\0')
		k++;
	var = ft_substr(str, j, k);
	if (var)
		return (var);
	return (NULL);
}

static char *search_var(char *str)
{
	int j;

	j = 0;
	while (str[j])
	{
		if (str[j] == '$')
			return (assign_var(str, j + 1));
		j++;
	}
	return (NULL);
}

static void replace_var(char **str, char *arg)
{
	char *before;
	int  i;

	i = 0;
	while ((*str)[i] != '$')
		i++;
	before = ft_substr(*str, 0, i);
	free(*str);
	*str = NULL;
	*str = ft_strjoin(before, arg);
}

static void get_var_arg(char **str, t_list_envp *ms_env)
{
	int i;
	int quote;
	char *var;
	char *arg;

	i = 0;
	while (str[i])
	{
		if (str[i][0] == '\'' || str[i][0] == '\"')
			quote = clean_quote(&str[i]);
		if (quote == 2)
			break ;
		var = search_var(str[i]);
		if (var)
		{
			arg = get_ms_env_val(var, ms_env);
			if (!arg)
				arg = ft_strdup("");
			replace_var(&str[i], arg);
		}
		i++;
	}
}

void convert_var(t_command **cmd, t_list_envp *ms_env)
{
	t_command *cur;
	t_simple_command *tmp;

	cur = *cmd;
	while (cur)
	{
		tmp = (*cur->list);
		while (tmp)
		{
			get_var_arg(&(*tmp->arg), ms_env);
			join_quotes(&(*tmp->arg));
			tmp = tmp->next;
		}
		cur = cur->next;
	}
}
