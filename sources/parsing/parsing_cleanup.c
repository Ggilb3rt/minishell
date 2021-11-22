/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cleanup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alangloi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 14:41:21 by alangloi          #+#    #+#             */
/*   Updated: 2021/11/09 14:41:24 by alangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
static void clean_simple(char **str)
{
	int i;
	int j;
	char *new;
	int spec;

	i = 1;
	spec = 0;
	new = malloc(sizeof(char) * (ft_strlen(*str) - 1));
	if (!new)
		return ;
	j = 0;
	while ((*str)[i] != '\'')
	{
		if ((*str)[i + 2] == '\2')
			spec = 1;
		new[j] = (*str)[i];
		i++;
		j++;
	}
	if (!spec)
		new[j] = '\0';
	else
		new[j] = '\2';
	free(*str);
	(*str) = new;
}

static void clean_double(char **str)
{
	int i;
	int j;
	char *new;
	int spec;

	i = 1;
	spec = 0;
	new = malloc(sizeof(char) * (ft_strlen(*str) - 1));
	if (!new)
		return ;
	j = 0;
	while ((*str)[i] != '\"')
	{
		if ((*str)[i + 2] == '\2')
			spec = 1;
		new[j] = (*str)[i];
		i++;
		j++;
	}
	if (!spec)
		new[j] = '\0';
	else
		new[j] = '\2';
	free(*str);
	(*str) = new;
}

int clean_quote(char **str)
{
	if ((*str[0]) == '\"')
	{
		clean_double(str);
		return (1);
	}
	if ((*str[0]) == '\'')
	{
		clean_simple(str);
		return (2);
	}
	return (0);
}
 */

/*
void join_quotes(char **str)
{
	int i;
	int j;
	int k;
	char *tmp;
	int join;

	j = 0;
	i = 0;
	while (str[i])
	{
		if (join)
		{
			k = 0;
			while (str[i + k])
			{
				if (str[i + k])
				{
					//printf("1\n");
					free(str[i + k]);
					str[i + k] = NULL;
				}
				if (str[i + k + 1])
				{
					str[i + k] = ft_strdup(str[i + k + 1]);
					//printf("2\n");
					//free(str[i + k + 1]);
					//str[i + k + 1] = NULL;
				}
				else
					break ;
				k++;
			}
			//i++;
		}
		join = 0;
		j = 0;
		//printf("1 %s\n", str[i]);
		while (str[i][j])
		{
			//printf("2 %c\n", str[i][j]);
			if (str[i][j + 1] == '\2')
			{
				//printf("3\n");
				//printf("\tstr[%i][%i + 1] = %c\n", i, j, str[i][j + 1]);
				tmp = ft_strdup(str[i]);
				free(str[i]);
				str[i] = ft_strjoin(tmp, str[i + 1]);
				free(tmp);
				join = 1;
			}
			j++;
		}
		//printf("JOIN QUOTE %i = %s\n", i, str[i]);
		i++;
	}
}
 */

static int 	open_quoteee(const char *str, t_split *split)
{
	if (str[split->i] == '\"' && !split->open_s && !split->open_d)
	{
		split->open_d = 1;
		split->i++;
		return (1);
	}
	if (str[split->i] == '\'' && !split->open_d && !split->open_s)
	{
		split->open_s = 1;
		split->i++;
		return (1);
	}
	return (0);
}

static int 	close_quoteee(const char *str, t_split *split)
{
	if (str[split->i] == '\"' && !split->open_s && split->open_d)
	{
		split->open_d = 0;
		split->i++;
		return (0);
	}
	if (str[split->i] == '\'' && !split->open_d && split->open_s)
	{
		split->open_s = 0;
		split->i++;
		return (0);
	}
	return (1);
}

static void	init_split(t_split *split, const char *str)
{
	(void)str;
	split->i = 0;
	split->l = 0;
	split->open_s = 0;
	split->open_d = 0;
}

static char *assign_varrr(const char *str, t_split *split)
{
	char *var;
	int k;

	split->i++;
	k = split->i;
	var = NULL;
	while (str[split->i] != ' ' && str[split->i] != '\0' && str[split->i] != '\'' && str[split->i] != '\"')
	{
		//printf("\t%c \n", str[split->i + k]);
		split->i++;
	}
	var = ft_substr(str, k, split->i - k);
	if (var)
		return (var);
	return (NULL);
}

static void search_varrr(const char *str, t_split *split, t_list_envp *ms_env)
{
	char *var;
	char *arg;
	int i;

	if (str[split->i] == '$')
	{
		var = assign_varrr(str, split);
		if (var)
		{
			arg = get_ms_env_val(var, ms_env);
			if (!arg)
				arg = ft_strdup("");
			i = 0;
			while (arg[i]) {
				split->new[split->l] = arg[i];
				split->l++;
				i++;
			}
			//split->i++;
		}
	}
}

static int ret_val(const char *str, t_split *split)
{
	int i;

	i = 0;
	while (str[split->i + i] && str[split->i + i] != ' ')
		i++;
	return (i);
}

static int redirection(char *str, t_split *split, t_command **cmd)
{
	int i;

	i = 0;
	if (str[split->i] == '<')
	{
		split->i++;
		while (str[split->i == ' '])
			split->i++;
		while (ft_isalnum(str[split->i]))
		{
			(*cmd)->in_file = malloc(sizeof(char) * (ret_val(str, split) + 1));
			if (ft_isalnum(str[split->i]))
			{
				(*cmd)->in_file[i] = str[split->i];
				split->i++;
				i++;
			}
		}
		(*cmd)->in_file[i] = '\0';
		return (0);
	}
	else if (str[split->i] == '>')
	{
		split->i++;
		while (str[split->i] == ' ')
			split->i++;
		while (str[split->i])
		{
			(*cmd)->out_file = malloc(sizeof(char) * (ret_val(str, split) + 1));
			if (ft_isalnum(str[split->i]))
			{
				(*cmd)->out_file[i] = str[split->i];
				split->i++;
				i++;
			}
		}
		(*cmd)->out_file[i] = '\0';
		return (0);
	}
	return (1);
}

void parsing_cleanup(char *str, t_list_envp *ms_env, t_command **cmd)
{
	t_split	split;
	t_command *cur;

	init_split(&split, str);
	split.new = malloc(sizeof(char) * 10000);
	cur = alloc_command(split.new);
	while (str[split.i])
	{
		if (str[split.i] == '|')
		{
			if (split.new)
			{
				add_command(cur, cmd);
				free(cur);
				cur = NULL;
				cur = alloc_command(split.new);
			}
			(*(*cmd)->list)->arg = plpl;
			split.i++;
			*cmd = (*cmd)->next;
			//----------------------
		}
		if (open_quoteee(str, &split))
		{
			while (close_quoteee(str, &split))
			{
				if (!split.open_s)
					search_varrr(str, &split, ms_env);
				split.new[split.l] = str[split.i];
				split.l++;
				split.i++;
			}
		}
		redirection(str, &split, cmd);
		split.new[split.l] = str[split.i];
		split.l++;
		split.i++;
	}
}