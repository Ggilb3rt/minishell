/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_split_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alangloi <alangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 11:02:33 by alangloi          #+#    #+#             */
/*   Updated: 2021/11/09 15:38:40 by alangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Theses functions are launched by find_quote in parsing_split_1.c and will be
 * the core of the spliting into different parts and be stored in slpt->new.
 */

void	open_quote(char *str, int i, t_split *splt)
{
	if (str[i] == '\'')
	{
		splt->count_s = i;
		splt->open = 1;
	}
	else if (str[i] == '\"')
	{
		splt->count_d = i;
		splt->open = 2;
	}
}

char	*split_words(char *str, int strt, int fnsh)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc(sizeof(char) * (fnsh - strt + 1));
	if (!word)
		return (NULL);
	while (strt < fnsh)
	{
		word[i] = str[strt];
		i++;
		strt++;
	}
	word[i] = '\0';
	return (word);
}

void	count_quote(char *str, int i, t_split *splt)
{
	if (splt->count_s > 0)
	{
		splt->new[splt->j] = split_words(str, splt->count_s, i + 1);
		splt->count_s = -1;
	}
	else if (splt->count_d > 0)
	{
		splt->new[splt->j] = split_words(str, splt->count_d, i + 1);
		splt->count_d = -1;
	}
	splt->j++;
	splt->open = 0;
}

void	count_spaces(char *str, int i, t_split *splt)
{
	splt->new[splt->j] = split_words(str, splt->count, i);
	splt->count = -1;
	splt->j++;
	if ((str[i] == '\"' || str[i] == '\'') && splt->open == 0
		&& splt->count < 0)
		open_quote(str, i, splt);
}
