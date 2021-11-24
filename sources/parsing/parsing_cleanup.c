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

static int	open_quoteee(const char *str, t_split *split)
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

static int	close_quoteee(const char *str, t_split *split)
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
	split->o = 0;
	split->q = 0;
	split->open_s = 0;
	split->open_d = 0;
}

static char	*assign_varrr(const char *str, t_split *split)
{
	char	*var;
	int		k;

	split->i++;
	k = split->i;
	var = NULL;
	while (str[split->i] != ' ' && str[split->i] != '\0' && str[split->i] != '\'' && str[split->i] != '\"')
		split->i++;
	var = ft_substr(str, k, split->i - k);
	if (var)
		return (var);
	return (NULL);
}

static int	search_varrr(const char *str, t_split *split, t_list_envp *ms_env)
{
	char *var;
	char *arg;

	if (str[split->i] == '$')
	{
		var = assign_varrr(str, split);
		if (var)
		{
			arg = get_ms_env_val(var, ms_env);
			if (!arg)
				arg = ft_strdup("");
			split->q = 0;
			while (arg[split->q])
			{
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

static int	ret_val(const char *str, t_split *split)
{
	int i;

	i = 0;
	while (str[split->i + i] && str[split->i + i] != ' ')
		i++;
	return (i);
}

static int	redirection(char *str, t_split *split, t_command *cmd)
{
	int i;

	i = 0;
	if (str[split->i] == '<' && str[split->i + 1] != '<')
	{
		split->i++;
		while (str[split->i == ' '])
			split->i++;
		cmd->in_file = malloc(sizeof(char) * (ret_val(str, split) + 1));
		while (str[split->i] && str[split->i] != ' ')
		{
			if (ft_isalnum(str[split->i]))
			{
				cmd->in_file[i] = str[split->i];
				split->i++;
				i++;
			}
		}
		cmd->token_in = LESS;
		cmd->token_out = 0;
		cmd->in_file[i] = '\0';
		return (0);
	}
	else if (str[split->i] == '>' && str[split->i + 1] != '>')
	{
		split->i++;
		while (str[split->i] == ' ')
			split->i++;
		cmd->out_file = malloc(sizeof(char) * (ret_val(str, split) + 1));
		while (str[split->i] && str[split->i] != ' ')
		{
			if (ft_isalnum(str[split->i]))
			{
				cmd->out_file[i] = str[split->i];
				split->i++;
				i++;
			}
		}
		cmd->token_in = 0;
		cmd->token_out = GREAT;
		cmd->out_file[i] = '\0';
		return (1);
	}
	else if (str[split->i] == '>' && str[split->i + 1] == '>')
	{
		split->i += 2;
		while (str[split->i] == ' ')
			split->i++;
		cmd->out_file = malloc(sizeof(char) * (ret_val(str, split) + 1));
		while (str[split->i] && str[split->i] != ' ')
		{
			if (ft_isalnum(str[split->i]))
			{
				cmd->out_file[i] = str[split->i];
				split->i++;
				i++;
			}
		}
		cmd->token_in = 0;
		cmd->token_out = DGREAT;
		cmd->out_file[i] = '\0';
		return (1);
	}
	else if (str[split->i] == '<' && str[split->i + 1] == '<')
	{
		split->i += 2;
		while (str[split->i] == ' ')
			split->i++;
		cmd->end = malloc(sizeof(char) * (ret_val(str, split) + 1));
		while (str[split->i] && str[split->i] != ' ')
		{
			if (ft_isalnum(str[split->i]))
			{
				cmd->end[i] = str[split->i];
				split->i++;
				i++;
			}
		}
		cmd->token_in = DLESS;
		cmd->token_out = 0;
		cmd->end[i] = '\0';
		g_ret.ret = EHERE;
		return (1);
	}
	return (0);
}

static int 	count_args(const char *str, int pos)
{
	t_split split;
	int count;

	count = 0;
	init_split(&split, str);
	split.i = pos;
	while (str[split.i] && str[split.i] != '|')
	{
		if (open_quoteee(str, &split))
		{
			while (close_quoteee(str, &split))
				split.i++;
		}
		else if (str[split.i] == ' ')
		{
			split.i++;
			while (str[split.i] == ' ')
				split.i++;
			if (!str[split.i] && str[split.i] == '|')
				return (count);
			count++;
		}
		else
			split.i++;
	}
	count++;
	return (count);
}

static int 	count_word(char *str, t_list_envp *ms_env, int pos)
{
	int count;
	t_split split;
	t_command *cur;

	count = 0;
	init_split(&split, str);
	cur = alloc_command(NULL);
	split.i = pos;
	while (str[split.i] && str[split.i] != ' ')
	{
		if (open_quoteee(str, &split))
		{
			while (close_quoteee(str, &split))
			{
				if (!split.open_s && split.open_d)
				{
					if (!search_varrr(str, &split, ms_env))
					{
						count++;
						split.i++;
					}
					else
						count += split.q;
				}
				else
				{
					split.i++;
					count++;
				}
			}
		}
		else
		{
			redirection(str, &split, cur);
			split.i++;
			count++;
		}
	}
	return (count);
}

static void	get_char(char *str, t_split *split)
{
	split->new[split->o][split->l] = str[split->i];
	split->l++;
	split->i++;
}

void	parsing_cleanup(char *str, t_list_envp *ms_env, t_command **cmd)
{
	t_split		split;
	t_command	*cur;

	init_split(&split, str);
	split.new = malloc(sizeof(char *) * (count_args(str, split.i) + 1));
	if (!split.new)
		return ;
	split.new[split.o] = malloc (sizeof(char) * (count_word(str, ms_env, split.i) + 1));
	if (!split.new[split.o])
		return ;
	cur = alloc_command(NULL);
	while (str[split.i])
	{
		if (str[split.i] == ' ')
		{
			split.i++;
			while (str[split.i] == ' ')
				split.i++;
			if (str[split.i] == '|')
				continue ;
			if (!str[split.i])
				break ;
			split.new[split.o][split.l] = '\0';
			split.o++;
			split.new[split.o] = NULL;
			split.new[split.o] = malloc (sizeof(char) * (count_word(str, ms_env, split.i) + 1));
			if (!split.new[split.o])
				break ;
			//printf("--------------------\n");
			split.l = 0;
		}
		else if (str[split.i] == '|')
		{
			split.i++;
			while (str[split.i] == ' ')
				split.i++;
			if (!str[split.i])
				break ;
			split.new[split.o][split.l] = '\0';
			split.new[split.o + 1] = NULL;
			cur->arg = split.new;
			cur->token = create_token(split.new[0]);
			split.o = 0;
			split.new = NULL;
			split.new = malloc(sizeof(char *) * (count_args(str, split.i) + 1));
			if (!split.new)
				break ;
			split.new[split.o] = malloc (sizeof(char) * (count_word(str, ms_env, split.i) + 1));
			if (!split.new[split.o])
				break ;
			split.l = 0;
			add_command(cur, cmd);
			cur = NULL;
			cur = alloc_command(NULL);
		}
		else if (open_quoteee(str, &split))
		{
			while (close_quoteee(str, &split))
			{
				if (!split.open_s && split.open_d)
				{
					if (!search_varrr(str, &split, ms_env))
						get_char(str, &split);
				}
				else
					get_char(str, &split);
			}
		}
		else
		{
			redirection(str, &split, cur);
			get_char(str, &split);
		}
	}
	split.new[split.o][split.l] = '\0';
	split.new[split.o + 1] = NULL;
	cur->arg = split.new;
	cur->token = create_token(split.new[0]);
	add_command(cur, cmd);
	cur = NULL;
	add_newline(cmd);
}