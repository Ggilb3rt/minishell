//
// Created by alangloi on 11/24/21.
//

#include "minishell.h"

static int 	count_check_args(t_split *split)
{
	int count;

	count = 0;
	if (open_quote(split))
	{
		while (close_quote(split))
			split->i++;
	}
	else if (split->str[split->i] == ' ')
	{
		split->i++;
		del_spaces(split);
		if (!split->str[split->i] || split->str[split->i] == '|')
			return (count);
		count++;
	}
	else
		split->i++;
	return (count);
}

int 	count_args(char *str, int pos)
{
	t_split split;
	int count;

	count = 0;
	init_split(&split, str);
	split.i = pos;
	while (split.str[split.i] && split.str[split.i] != '|')
		count += count_check_args(&split);
	count++;
	printf("count args = %d\n", count);
	return (count);
}

static int count_open_quote(t_split *split, t_list_envp *ms_env)
{
	int count;

	count = 0;
	while (close_quote(split))
	{
		if (!split->open_s && split->open_d)
		{
			if (!search_var(split, ms_env, 0))
			{
				count++;
				split->i++;
			}
			else
				count += split->q;
		}
		else
		{
			split->i++;
			count++;
		}
	}
	return (count);
}

int 	count_word(char *str, t_list_envp *ms_env, int pos)
{
	int count;
	t_split split;
	t_command *cur;

	count = 0;
	init_split(&split, str);
	cur = alloc_command(NULL);
	split.i = pos;
	while (split.str[split.i] && split.str[split.i] != ' ')
	{
		if (open_quote(&split))
			count += count_open_quote(&split, ms_env);
		else
		{
			redirection(&split, &cur);
			if (!search_var(&split, ms_env, 0))
			{
				split.i++;
				count++;
			}
			else
				count += split.q;
		}
	}
	printf("count words = %d\n", count);
	return (count);
}