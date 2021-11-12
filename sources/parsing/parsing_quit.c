/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alangloi <alangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 14:28:12 by alangloi          #+#    #+#             */
/*   Updated: 2021/10/19 14:28:13 by alangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void 	free_split(t_split *splt)
{
	while ((*splt->new))
	{
		free((*splt->new));
		(*splt->new) = NULL;
		splt->new++;
	}
}

void 	free_word(char *word)
{
	if (word)
	{
		free(word);
		word = NULL;
	}
}