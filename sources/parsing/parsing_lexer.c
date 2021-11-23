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
/*
static void	new_simple_command(char *arg, t_simple_command **list)
{
	t_simple_command	*cur;

	cur = alloc_simple(arg);
	if (!cur)
		return ;
	add_simple(cur, list);
}
 */
/*
static void	new_command(char **arg, t_command **cmd, int end, int begin)
{
	t_command	*cur;

	cur = alloc_command(arg);
	if (!cur)
		return ;
	add_command(cur, cmd);
}
*/
/*
static t_simple_command	**init_list(void)
{
	t_simple_command	**list;

	list = malloc(sizeof(t_simple_command *));
	if (!list)
		return (NULL);
	*list = NULL;
	return (list);
}

t_simple_command	**get_simple(char *arg)
{
	t_simple_command	**list;

	list = NULL;
	list = init_list();
	new_simple_command(arg, list);
	return (list);
}
*/
/*
 * The lexing part is processed into 2 differents step :
 * - First step, we are handling all the pipes
 * - Second step, we are handling the chevrons.
 */

/*
t_command	**get_command(char *arg, t_command **cmd)
{
	int			begin;
	int			i;

	i = 0;
	begin = 0;
	while (arg[i])
	{
		if (!ft_strcmp(arg[i], "|"))
		{
			arg[i] = NULL;
			new_command(arg, cmd, i, begin);
			begin = i + 1;
		}
		i++;
	}
	new_command(arg, cmd, i, begin);
	if (!add_newline(cmd, arg, array_size(arg)))
		return (NULL);
	return (cmd);
}
*/