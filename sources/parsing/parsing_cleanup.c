/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cleanup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alangloi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 14:41:21 by alangloi          #+#    #+#             */
/*   Updated: 2021/11/09 14:41:24 by alangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int clean_simple(char **str)
{
	int i;
	int j;
	int s;
	char *new;

	i = 1;
	s = 0;
	new = malloc(sizeof(char) * (ft_strlen(*str) - 1));
	if (!new)
		return (2);
	j = 0;
	while ((*str)[i] != '\'')
	{
		new[j] = (*str)[i];
		i++;
		j++;
	}
	new[j] = '\0';
	s = 2;
	free(*str);
	(*str) = new;
	return (s);
}

int clean_double(char **str)
{
	int i;
	int j;
	int d;
	char *new;

	i = 1;
	d = 0;
	new = malloc(sizeof(char) * (ft_strlen(*str) - 1));
	if (!new)
		return (2);
	j = 0;
	while ((*str)[i] != '\"')
	{
		new[j] = (*str)[i];
		i++;
		j++;
	}
	new[j] = '\0';
	d = 1;
	free(*str);
	(*str) = new;
	return (d);
}

int clean_quote(char **str)
{
	int ret;

	ret = 0;
	if ((*str[0]) == '\"')
		ret = clean_double(str);
	if ((*str[0]) == '\'')
		ret = clean_simple(str);
	return (ret);
}