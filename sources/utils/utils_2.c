/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 14:05:41 by alangloi          #+#    #+#             */
/*   Updated: 2021/10/26 16:07:56 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_countc(char const *s, char c)
{
	int	i;

	i = 0;
	while (*s)
	{
		if (*s == c)
		{
			i++;
			while (*s && *s == c)
				s++;
		}
		if (*s != '\0')
			s++;
	}
	return (i);
}

char	*w_malloc(char *s, char c)
{
	char	*word;
	int		i;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
		i++;
	word = (char *)malloc(sizeof(char) * (i + 1));
	if (word == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0' && s[i] != c)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	*process(char *sn, char c, char **arr)
{
	int	i;

	i = 0;
	while (*sn)
	{
		if (*sn != c && *sn)
		{
			arr[i] = w_malloc(sn, c);
			if (arr[i] == NULL)
				return (NULL);
			i++;
			while (*sn && *sn != c)
				sn++;
		}
		if (*sn != '\0')
			sn++;
	}
	arr[i] = NULL;
	return (sn);
}

char	**ms_split(char const *s, char c)
{
	char	**arr;
	char	*sn;

	sn = ft_strtrim(s, &c);
	if (!sn)
		return (NULL);
	arr = (char **)malloc(sizeof(s) * (ft_countc(sn, c) + 2));
	if (arr == NULL)
		return (NULL);
	process(sn, c, arr);
	free(sn);
	return (arr);
}

char	*ms_strjoin(char const *s1, char const *s2)
{
	char	*c;
	size_t	s1l;
	size_t	s2l;

	if (s1 == NULL || s2 == NULL)
		return (0);
	s1l = ms_strlen(s1);
	s2l = ms_strlen(s2);
	c = malloc((s1l + s2l + 1) * sizeof(*c));
	if (c == NULL)
		return (0);
	while (*s1)
	{
		*c = *s1;
		c++;
		s1++;
	}
	while (*s2)
	{
		*c = *s2;
		c++;
		s2++;
	}
	*c = '\0';
	return (c - s1l - s2l);
}
