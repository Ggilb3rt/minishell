/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_lexer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 14:18:38 by alangloi          #+#    #+#             */
/*   Updated: 2021/10/22 14:11:59 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_arg(char **str, int i, int last)
{
	char	**new;
	int		diff;
	int		j;

	j = 0;
	diff = i - last;
	new = malloc(sizeof(char *) * diff + 1);
	if (!new)
		return (0);
	while (j < diff)
	{
		new[j] = ms_strdup(str[last + j]);
		j++;
	}
	new[j] = NULL;
	return (new);
}

static int	convert(t_simple_command **list, char **arg, int i, int cur)
{
	char				**new;
	t_simple_command	*elem;

	if (cur != 0)
		cur++;
	new = get_arg(arg, i, cur);
	elem = alloc_simple(new);
	add_simple(elem, list);
	if (arg[i] != NULL)
	{
		cur = i;
		new = get_arg(arg, i + 1, cur);
		elem = alloc_simple(new);
		add_simple(elem, list);
	}
	return (cur);
}

t_simple_command	**lexer_2(char **arg, int begin, int end)
{
	t_simple_command	**list;
	int					i;
	int					cur;

	i = begin;
	cur = begin;
	list = malloc(sizeof(t_simple_command *));
	if (!list)
		return (NULL);
	while (i < end)
	{
		if (!ms_strcmp(arg[i], "<") || !ms_strcmp(arg[i], ">")
			|| !ms_strcmp(arg[i], "<<") || !ms_strcmp(arg[i], ">>"))
			cur = convert(list, arg, i, cur);
		i++;
	}
	if (i - cur > 0)
		cur = convert(list, arg, i, cur);
	return (list);
}

/*
 * The lexing part is processed into 2 differents step :
 * - First step, we are handling all the pipes
 * - Second step, we are handling the chevrons.
 */

t_command	**lexer(char **arg, t_command **cmd)
{
	t_command	*cur;
	int			begin;
	int			i;

	*cmd = NULL;
	cur = *cmd;
	i = 0;
	begin = 0;
	while (arg[i])
	{
		if (!ms_strcmp(arg[i], "|"))
		{
			cur = alloc_command(arg, begin, i);
			add_command(cur, cmd);
			begin = i;
		}
		i++;
	}
	cur = alloc_command(arg, begin, i);
	add_command(cur, cmd);
	add_newline(&cur, arg, array_size(arg));
	return (cmd);
}
