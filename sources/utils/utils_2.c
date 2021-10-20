/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alangloi <alangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 14:05:41 by alangloi          #+#    #+#             */
/*   Updated: 2021/10/19 14:08:35 by alangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	numb_words(const char *str, char c)
{
	int	i;
	int	trig;

	i = 0;
	trig = 0;
	while (*str)
	{
		if (*str != c && trig == 0)
		{
			trig = 1;
			i++;
		}
		else if (*str == c)
			trig = 0;
		str++;
	}
	return (i);
}

static char	*sep_words(const char *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((finish - start + 1) * sizeof(char));
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

char	*fill_array(const char *s, int *count, int i, char c)
{
	if (s[i] != c && *count < 0)
		*count = i;
	else if ((s[i] == c || i == (int)ms_strlen(s)) && *count >= 0)
	{
		return (sep_words(s, *count, i));
	}
	return (NULL);
}

char	**ms_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	int		count;
	char	**arr;

	i = 0;
	j = 0;
	arr = malloc(sizeof(char *) * (numb_words(s, c) + 1));
	if (!arr)
		return (0);
	count = -1;
	while (i <= ms_strlen(s))
	{
		arr[j++] = fill_array(s, &count, i, c);
		if (arr[j])
			count = -1;
		i++;
	}
	arr[j] = 0;
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
