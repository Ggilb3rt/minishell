//
// Created by Antoine LANGLOIS on 02/11/2021.
//

#include "minishell.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s != (char)c)
			s++;
		else
			return ((char *)s);
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (0);
}