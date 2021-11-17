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

static void clean_simple(char **str)
{
	int i;
	int j;
	char *new;
	int spec;

	i = 1;
	spec = 0;
	new = malloc(sizeof(char) * (ft_strlen(*str) - 1));
	if (!new)
		return ;
	j = 0;
	while ((*str)[i] != '\'')
	{
		if ((*str)[i + 2] == '\2')
			spec = 1;
		new[j] = (*str)[i];
		i++;
		j++;
	}
	if (!spec)
		new[j] = '\0';
	else
		new[j] = '\2';
	free(*str);
	(*str) = new;
}

static void clean_double(char **str)
{
	int i;
	int j;
	char *new;
	int spec;

	i = 1;
	spec = 0;
	new = malloc(sizeof(char) * (ft_strlen(*str) - 1));
	if (!new)
		return ;
	j = 0;
	while ((*str)[i] != '\"')
	{
		if ((*str)[i + 2] == '\2')
			spec = 1;
		new[j] = (*str)[i];
		i++;
		j++;
	}
	if (!spec)
		new[j] = '\0';
	else
		new[j] = '\2';
	free(*str);
	(*str) = new;
}

int clean_quote(char **str)
{
	if ((*str[0]) == '\"')
	{
		clean_double(str);
		return (1);
	}
	if ((*str[0]) == '\'')
	{
		clean_simple(str);
		return (2);
	}
	return (0);
}
/*
void join_quotes(char **str)
{
	int i;
	int j;
	int k;
	char *tmp;
	int join;

	j = 0;
	i = 0;
	while (str[i])
	{
		if (join)
		{
			k = 0;
			while (str[i + k])
			{
				if (str[i + k])
				{
					//printf("1\n");
					free(str[i + k]);
					str[i + k] = NULL;
				}
				if (str[i + k + 1])
				{
					str[i + k] = ft_strdup(str[i + k + 1]);
					//printf("2\n");
					//free(str[i + k + 1]);
					//str[i + k + 1] = NULL;
				}
				else
					break ;
				k++;
			}
			//i++;
		}
		join = 0;
		j = 0;
		//printf("1 %s\n", str[i]);
		while (str[i][j])
		{
			//printf("2 %c\n", str[i][j]);
			if (str[i][j + 1] == '\2')
			{
				//printf("3\n");
				//printf("\tstr[%i][%i + 1] = %c\n", i, j, str[i][j + 1]);
				tmp = ft_strdup(str[i]);
				free(str[i]);
				str[i] = ft_strjoin(tmp, str[i + 1]);
				free(tmp);
				join = 1;
			}
			j++;
		}
		//printf("JOIN QUOTE %i = %s\n", i, str[i]);
		i++;
	}
}
 */