//
// Created by antoine on 15/11/2021.
//

#include "minishell.h"

char *ft_substr(const char *s, unsigned int start, size_t len)
{
	char *str;
	size_t	i;

	if (!s)
		return (NULL);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	if (start < ft_strlen(s))
	{
		while (i < len && s[i + start] != '\0')
		{
			str[i] = s[start + i];
			i++;
		}
	}
	str[i] = '\0';
	return (str);
}