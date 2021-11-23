/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alangloi <alangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 14:28:12 by alangloi          #+#    #+#             */
/*   Updated: 2021/10/19 14:28:13 by alangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_error(char *str, int fd)
{
	int i;

	i = 0;
	while (str[i])
	{
		write(fd, &str[i], 1);
	}
	write(fd, "\n", 1);
}



void free_split(t_split *splt)
{
	free(splt->new);
	splt->new = NULL;
	free(splt);
	splt = NULL;
}

void free_word(char *str)
{
	free(str);
	str = NULL;
}

/*
void free_count(t_count *cnt)
{
	int i;

	i = 0;
	while (cnt)
}
*/