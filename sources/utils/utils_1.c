/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alangloi <alangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 14:08:51 by alangloi          #+#    #+#             */
/*   Updated: 2021/10/19 14:08:53 by alangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	array_size(char **arr)
{
	int	i;

	i = 0;
	if (!arr || !*arr)
		return (0);
	while (arr[i])
		i++;
	return (i);
}

int	arr_int_size(int *arr)
{
	int	i;

	i = 0;
	if (!arr || !*arr)
		return (0);
	while (arr[i])
		i++;
	return (i);
}
