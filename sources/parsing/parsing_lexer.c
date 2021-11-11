/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_lexer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 14:18:38 by alangloi          #+#    #+#             */
/*   Updated: 2021/11/09 15:58:44 by alangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_arg(char **str, int begin, int end)
{
	char	**new;
	int		diff;
	int		j;

	j = 0;
	diff = end - begin;
	new = malloc(sizeof(char *) * (diff + 1));
	if (!new)
		return (NULL);
	while (j < diff)
	{
		new[j] = ft_strdup(str[begin + j]);
		j++;
	}
	new[j] = NULL;
	return (new);
}

static void	new_simple_command(char **arg, t_simple_command **list,
								  int end, int begin)
{
	t_simple_command	*cur;

	cur = alloc_simple(arg, begin, end);
	if (!cur)
		return ;
	add_simple(cur, list);
}

static void	new_command(char **arg, t_command **cmd, int end, int begin)
{
	t_command	*cur;

	cur = alloc_command(arg, begin, end);
	if (!cur)
		return ;
	add_command(cur, cmd);
}

static t_simple_command **init_list(void)
{
	t_simple_command **list;

	list = malloc(sizeof(t_simple_command *));
	if (!list)
		return (NULL);
	*list = NULL;
	return (list);
}

t_simple_command	**lexer_2(char **arg, int begin, int end)
{
	t_simple_command	**list;
	int					i;

	i = begin;
	list = NULL;
	list = init_list();
	while (i < end)
	{
		if (!ft_strcmp(arg[i], "<") || !ft_strcmp(arg[i], ">")
			|| !ft_strcmp(arg[i], "<<") || !ft_strcmp(arg[i], ">>"))
		{
			if (i - begin == 0)
				i++;
			new_simple_command(arg, list, i, begin);
			begin = i;
		}
		i++;
	}
	new_simple_command(arg, list, i, begin);
	return (list);
}

/*
 * The lexing part is processed into 2 differents step :
 * - First step, we are handling all the pipes
 * - Second step, we are handling the chevrons.
 */

t_command	**lexer(char **arg, t_command **cmd)
{
	int			begin;
	int			i;

	i = 0;
	begin = 0;
	while (arg[i])
	{
		if (!ft_strcmp(arg[i], "|"))
		{
			new_command(arg, cmd, i, begin);
			begin = i;
		}
		i++;
	}
	new_command(arg, cmd, i, begin);
	if (!add_newline(cmd, arg, array_size(arg)))
		return (NULL);
	return (cmd);
}
