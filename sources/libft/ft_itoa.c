/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 12:22:25 by ggilbert          #+#    #+#             */
/*   Updated: 2021/11/24 11:10:41 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_intl(int n, size_t len)
{
	if (n / 10 == 0)
		return (++len);
	n = n / 10;
	len++;
	len = ft_intl(n, len);
	return (len);
}

char	*ft_strrev(char *s, size_t len)
{
	char	*temp;
	size_t	base_len;
	size_t	i;

	i = 0;
	base_len = len;
	temp = malloc(sizeof(char) * len + 1);
	if (temp == NULL)
		return (NULL);
	while (len > 0)
	{
		temp[i] = s[len - 1];
		i++;
		len--;
	}
	i = 0;
	while (i < base_len)
	{
		s[i] = temp[i];
		i++;
	}
	s[i] = '\0';
	free(temp);
	return (s);
}

long	ft_calc(int n)
{
	long	res;

	res = 0;
	res = n % 10;
	if (res < 0)
		res *= -1;
	return (res);
}

char	*ft_itoa(int n)
{
	char	*s;
	long	res;
	int		isneg;
	size_t	nlen;

	res = 0;
	isneg = 0;
	nlen = ft_intl(n, 0);
	if (n < 0)
		isneg = nlen++;
	s = malloc((sizeof(*s) * nlen + 1));
	if (s == NULL)
		return (0);
	if (n == 0)
		*s++ = '0';
	while (n != 0)
	{
		res = ft_calc(n);
		*s++ = res + '0';
		n /= 10;
	}
	if (isneg)
		*s++ = '-';
	ft_strrev(s - nlen, nlen);
	return (s - nlen);
}
