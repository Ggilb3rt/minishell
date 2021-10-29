/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_elem.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alangloi <alangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 14:16:40 by alangloi          #+#    #+#             */
/*   Updated: 2021/10/19 14:29:39 by alangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_simple_command	*alloc_simple(char **str)
{
	t_simple_command	*new;

	new = malloc(sizeof(t_simple_command));
	if (!new)
		return (NULL);
	new->arg = str;
	new->token = create_token(new->arg[0]);
	new->numb_avail = 0;
	new->numb = 0;
	new->next = NULL;
	return (new);
}

t_command	*alloc_command(char **arg, int begin, int end)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->numb_avail_simple_commands = 0;
	cmd->numb_simple_commands = 0;
	cmd->list = lexer_2(arg, begin, end);
	cmd->out_file = ms_strdup("dflt");
	cmd->in_file = ms_strdup("dflt");
	cmd->err_file = ms_strdup("dflt");
	cmd->next = NULL;
	return (cmd);
}
