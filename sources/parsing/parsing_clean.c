/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_clean.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alangloi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 17:46:22 by alangloi          #+#    #+#             */
/*   Updated: 2021/12/01 17:46:25 by alangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	count_semi_slash(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '\\' || str[i] == ';')
			count++;
		i++;
	}
	return (count);
}

char	*cleanup_string(char *str)
{
	char	*new;
	int		i;
	int		j;
	int		len;

	j = 0;
	i = 0;
	len = ft_strlen(str);
	new = malloc(sizeof(char) * (len - count_semi_slash(str) + 1));
	while (j < len)
	{
		while (str[j] == '\\' || str[j] == ';')
			j++;
		new[i] = str[j];
		i++;
		j++;
	}
	new[i] = '\0';
	printf("\t%s[%d]\n", new, len - count_semi_slash(str) + 1);
	free(str);
	str = NULL;
	return (new);
}
