//
// Created by Antoine LANGLOIS on 23/09/2021.
//

#include "utils.h"

static int 	numb_words(const char *str, char c)
{
	int 	i;
	int 	trig;

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
	char 	*word;
	int 	i;

	i = 0;
	word = malloc((finish - start + 1) * sizeof(char));
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

int	ms_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	int 	count;
	char 	**tab;

	i = 0;
	j = 0;
	if (!s)
		return (0);
	tab = malloc(sizeof(char *) * (numb_words(s, c) + 1));
	if (!tab)
		return (0);
	count = -1;
	while (i <= ms_strlen(s))
	{
		if (s[i] != c && count < 0)
			count = i;
		else if ((s[i] == c || i = ms_strlen(s)) && count >= 0)
		{
			tab[j++] = sep_words(s, count, i);
			count = -1;
		}
		i++;
	}
	tab[j] = 0;
	return (tab);
}