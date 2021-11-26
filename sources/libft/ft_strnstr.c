/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alangloi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 14:37:45 by alangloi          #+#    #+#             */
/*   Updated: 2021/11/26 14:37:49 by alangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
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
