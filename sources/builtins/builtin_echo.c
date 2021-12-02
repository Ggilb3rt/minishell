/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 11:54:18 by ggilbert          #+#    #+#             */
/*   Updated: 2021/12/02 13:22:55 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* echo with option -n : echo 'string'
 * - echo writes the string entered as an argument on the standard output
 * the option -n don't output the trailing newline
 */

int	is_flag(char *str)
{
	int	len;
	int	i;

	if (!str)
		return (0);
	len = ft_strlen(str);
	i = 1;
	if (str[0] == '-')
	{
		while (i < len && str[i] == 'n')
			i++;
		if (i == len)
			return (1);
	}
	return (0);
}

void	print_words(char **words, int flag)
{
	int		i;
	int		nb_words;

	i = 1;
	nb_words = array_size(words);
	if (flag)
		i++;
	while (i < nb_words)
	{
		if (!is_flag(words[i]))
			break ;
		i++;
	}
	while (i < nb_words)
	{
		printf("%s", words[i]);
		if (i + 1 < nb_words)
			printf(" ");
		i++;
	}
	if (!flag)
		printf("\n");
}

int	cmd_echo(char **words)
{
	int		flag;

	if (!words || !words[0])
	{
		printf("\n");
		return (0);
	}
	flag = is_flag(words[1]);
	print_words(words, flag);
	g_ret.ret = 0;
	return (0);
}
