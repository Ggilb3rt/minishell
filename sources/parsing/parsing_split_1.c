/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_split_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alangloi <alangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 16:09:05 by alangloi          #+#    #+#             */
/*   Updated: 2021/10/20 16:09:07 by alangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_split(t_split *splt, char *str)
{
	splt->new = malloc(sizeof(char *) * splt->size + 1);
	if (!splt->new)
		return ;
	splt->open = 0;
	splt->count = -1;
	splt->count_s = -1;
	splt->count_d = -1;
	splt->size = word_count(str);
	splt->len = ms_strlen(str);
	splt->j = 0;
}

/*
 * This function is the core of the split because it's here that we're going
 * to developp the algorithm.
 */

static void	find_quote(char *str, int i, t_split *splt)
{
	if ((str[i] == '\"' || str[i] == '\'') && splt->open == 0
		&& splt->count < 0)
		open_quote(str, i, splt);
	else if (splt->open == 0 && str[i] != ' ' && splt->count < 0)
		splt->count = i;
	else if (((str[i] == '\"' && splt->count_d >= 0)
			|| (str[i] == '\'' && splt->count_s >= 0))
		&& splt->open)
		count_quote(str, i, splt);
	else if ((str[i] == ' ' || i == splt->len || str[i] == '\"')
		&& splt->open == 0 && splt->count >= 0)
		count_spaces(str, i, splt);
}

/*
 * This function will split the string into different parts, caring about
 * the spaces but not only because the simple and double quotes will have
 * an influence on how the string will be splitted.
 */

char	**split_quote(char *str)
{
	int		i;
	t_split	*splt;

	splt = malloc(sizeof(t_split));
	init_split(splt, str);
	i = 0;
	while (i <= splt->len)
	{
		find_quote(str, i, splt);
		i++;
	}
	splt->new[splt->j] = 0;
	return (splt->new);
}
