/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 14:16:21 by alangloi          #+#    #+#             */
/*   Updated: 2021/11/09 15:48:15 by alangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Handling the entered string for filling the structures t_simple_command and
 * t_command declared in the main header file will be divided into two different
 * tasks :
 * - The first task will be the splitting part, when the string entered in the
 * prompt will be splitted into different parts.
 * - The second task will be the lexing part, when the array of words will be
 * converted into 'tokens' that will precise for later the type of argument
 * that we have to handle. Theses tokens are defined in the main header too.
 * This array will be converted into a linked list.
 * - The third task will be the parsing part, when the different tokens will be
 * sort in a maner that will indicate the type of information stored into the
 * differents parts of the string, and deal with the priority of theses parts.
 */

/*
 * To do : handling error and frees by adding functions to parsing_error.c.
 * The parsing is not perfect and will still need some improvements.
 */

void del_spaces(t_split *split)
{
	while (split->str[split->i] == ' ')
		split->i++;
}

int	ret_val(t_split *split)
{
	int i;

	i = 0;
	while (split->str[split->i + i] && split->str[split->i + i] != ' ')
		i++;
	return (i);
}

static int check_char(t_split *split, t_command *cur, t_command **cmd, t_list_envp *ms_env)
{
	if (split->str[split->i] == ' ')
	{
		if (!get_word_space(split, ms_env))
			return (0);
	}
	else if (split->str[split->i] == '|')
	{
		if (!get_arg_pipe(split, cur, cmd))
			return (0);
		if (!init_arg(split, cur, ms_env))
		{
			free_split(split);
			exit(0);
		}
	}
	else if (open_quote(split))
		into_quote(split, ms_env);
	else
	{
		redirection(split, cur);
		get_char(split);
	}
	return (1);
}

int	parsing_main(char *str, t_command **cmd, t_list_envp *ms_env)
{
	t_split		split;
	t_command	cur;
	int 		ret;

	split.new = NULL;
	init_split(&split, str);
	if (!init_arg(&split, &cur, ms_env))
	{
		free_split(&split);
		exit(0);
	}
	while (split.str[split.i])
	{
		ret = check_char(&split, &cur, cmd, ms_env);
		if (!ret)
			break ;
	}
	get_arg(&split, &cur, cmd);
	add_newline(cmd);
	/*
	for (t_command *tmp = *cmd; tmp != NULL; tmp = tmp->next)
	{
		for (int j = 0; j < array_size(tmp->arg); j++)
			printf("\t\t%s\n", tmp->arg[j]);
	}
	 */
	return (1);
}
