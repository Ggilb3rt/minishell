/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_lexer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alangloi <alangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 14:18:38 by alangloi          #+#    #+#             */
/*   Updated: 2021/10/19 14:21:46 by alangloi         ###   ########.fr       */
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
	elem = alloc_elem(new);
	add_elem(elem, list);
	if (arg[i] != NULL)
	{
		cur = i;
		new = get_arg(arg, i + 1, cur);
		elem = alloc_elem(new);
		add_elem(elem, list);
	}
	return (cur);
}

t_simple_command	**lexer(char **arg)
{
	t_simple_command	**list;
	int					i;
	int					cur;

	i = 0;
	cur = 0;
	list = malloc(sizeof(t_simple_command *));
	if (!list)
		return (NULL);
	while (arg[i])
	{
		if (!ms_strcmp(arg[i], "<") || !ms_strcmp(arg[i], ">")
			|| !ms_strcmp(arg[i], "|") || !ms_strcmp(arg[i], "<<")
			|| !ms_strcmp(arg[i], ">>"))
			cur = convert(list, arg, i, cur);
		i++;
	}
	if (i - cur > 0)
		cur = convert(list, arg, i, cur);
	add_newline(list, arg, i);
	//print_simple_command(list);
	return (list);
}
