/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 11:54:18 by ggilbert          #+#    #+#             */
/*   Updated: 2021/11/24 11:54:22 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* echo with option -n : echo 'string'
 * - echo writes the string entered as an argument on the standard output
 * the option -n don't output the trailing newline
 */

int	is_flag(char *str)
{
	if (!str)
		return (0);
	if (ft_strlen(str) == 2)
	{
		if (str[0] == '-' && str[1] == 'n')
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

	if (!words)
		return (1);
	flag = is_flag(words[1]);
	print_words(words, flag);
	return (0);
}
