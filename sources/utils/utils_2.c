//
// Created by Antoine LANGLOIS on 23/09/2021.
//

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

char	**ms_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	int		count;
	char	**arr;

	i = 0;
	j = 0;
	if (!s)
		return (0);
	arr = malloc(sizeof(char *) * (numb_words(s, c) + 1));
	if (!arr)
		return (0);
	count = -1;
	while (i <= ms_strlen(s))
	{
		if (s[i] != c && count < 0)
			count = i;
		else if ((s[i] == c || i == ms_strlen(s)) && count >= 0)
		{
			arr[j++] = sep_words(s, count, i);
			count = -1;
		}
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
