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

char	*split_words(char *str, int begin, int end, int nospace)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc(sizeof(char) * (end - begin + 1));
	if (!word)
		return (NULL);
	while (begin < end)
	{
		word[i] = str[begin];
		i++;
		begin++;
	}
	if (!nospace)
		word[i] = '\0';
	else {
		//printf("special case = %s\n", word);
		word[i] = '\2';
	}
	return (word);
}

void	count_quote(char *str, int i, t_split *splt)
{
	int nospace;

	nospace = 0;
	if ((str[i] == '\"' || str[i] == '\'') && (str[i + 1] != ' '))
	{
		//printf("yo\n");
		nospace = 1;
	}
	if (splt->count_s > 0)
	{
		splt->new[splt->j] = split_words(str, splt->count_s, i + 1, nospace);
		splt->count_s = -1;
	}
	else if (splt->count_d > 0)
	{
		splt->new[splt->j] = split_words(str, splt->count_d, i + 1, nospace);
		splt->count_d = -1;
	}
	splt->j++;
	splt->open = 0;
}

void	count_spaces(char *str, int i, t_split *splt)
{
	int nospace;

	nospace = 0;
	if ((str[i] == '\"' || str[i] == '\'') && (str[i - 1] != ' '))
	{
		//printf("ya\n");
		nospace = 1;
	}
	//printf("pipi [%c %c %c]\n", str[i - 1], str[i], str[i + 1]);
	splt->new[splt->j] = split_words(str, splt->count, i, nospace);
	//printf("\t\t%s\n", splt->new[splt->j]);
	splt->count = -1;
	splt->j++;
	if ((str[i] == '\"' || str[i] == '\'') && splt->open == 0
		&& splt->count < 0)
	{
		//printf("prout [%c %c %c]\n", str[i - 1], str[i], str[i + 1]);
		open_quote(str, i, splt);
	}
}
