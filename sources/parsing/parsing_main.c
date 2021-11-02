/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 14:16:21 by alangloi          #+#    #+#             */
/*   Updated: 2021/10/22 17:36:13 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Handling the entered string for filling the structures t_simple_command and
 * t_command declared in the main header file will be divided into two different
 * tasks :
 * - The first task will be the splitting part, when the string entered in the
 * prompt will be splitted into different parts.
 * - The second task will be the lexing part, when the array of words will be
 * converted into 'tokens' that will precise for later the type of argument
 * that we have to handle. Theses tokens are defined in the main header too.
 * This array will be converted into a linked list.
 * - The third task will be the parsing part, when the different tokens will be
 * sort in a maner that will indicate the type of information stored into the
 * differents parts of the string, and deal with the priority of theses parts.
 */

/*
 * To do : handling error and frees by adding functions to parsing_error.c.
 * The parsing is not perfect and will still need some improvements.
 */

int	lexer_and_parser(char *str, t_command **cmd)
{
	char	**arg;
	int		ret;

	//cleanup(&str);
	arg = split_quote(str);
	lexer(arg, cmd);
	if (!cmd)
	{
		printf("Error input string\n");
		exit (0);
	}
	ret = parser(cmd);
	if (!ret)
	{
		printf("Error synthax\n");
		exit (0);
	}
	return (ret);
}
