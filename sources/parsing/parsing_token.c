/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alangloi <alangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 14:10:22 by alangloi          #+#    #+#             */
/*   Updated: 2021/10/19 14:13:37 by alangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_operator(char *str)
{
	if (!ft_strcmp(str, ">"))
		return (GREAT);
	else if (!ft_strcmp(str, "<"))
		return (LESS);
	else if (!ft_strcmp(str, ">>"))
		return (DGREAT);
	else if (!ft_strcmp(str, "<<"))
		return (DLESS);
	else if (!ft_strcmp(str, "|"))
		return (PIPE);
	return (0);
}

int	create_token(char *str)
{
	if (is_operator(str))
		return (is_operator(str));
	else if (!ft_strcmp(str, "/"))
		return (NWLINE);
	else
		return (WORD);
}
