//
// Created by Antoine LANGLOIS on 22/09/2021.
//

#include "utils.h"

/* external functions that we may use :
 * - ssize_t write(int fd, const void *buf, size_t count) : writes until 'count' bytes in the file descriptor from the
 * buffer pointed by 'buf'.
 */

size_t	ms_strlen(const char *str)
{
	int	i;

	i = 0;
	while (*str++)
		i++;
	return (i);
}

int	ms_strcmp(const char *s1, const char *s2)
{
	const unsigned char	*p1;
	const unsigned char	*p2;
	unsigned char		c1;
	unsigned char		c2;

	p1 = (const unsigned char *)s1;
	p2 = (const unsigned char *)s2;
	c1 = *p1;
	c2 = *p2;
	while (c1 == c2)
	{
		c1 = (unsigned char)*p1++;
		c2 = (unsigned char)*p2++;
		if (c1 == '\0')
			return (c1 - c2);
	}
	return (c1 - c2);
}

char	*ms_strdup(const char *s)
{
	char	*str;
	int		len;
	int		i;

	i = 0;
	len = ms_strlen(s) + 1;
	str = malloc(sizeof(char) * len);
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	ms_is_alpha(const char *str)
{
	while (*str)
	{
		if ((*str < 'a' || *str > 'z')
			&& (*str < 'A' || *str > 'Z')
			&& (*str != '-') && (*str != '/'))
			return (0);
		str++;
	}
	return (1);
}

char	*ms_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*start;
	char	*pattern;
	size_t	c;

	while (*haystack && len)
	{
		start = (char *)haystack;
		pattern = (char *)needle;
		c = len;
		while (*haystack && *pattern && *haystack == *pattern && c)
		{
			haystack++;
			pattern++;
			c--;
		}
		if (!*pattern)
			return (start);
		haystack = start + 1;
		len--;
	}
	if (!*needle)
		return ((char *)haystack);
	return (0);
}
