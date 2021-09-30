/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 14:36:36 by ggilbert          #+#    #+#             */
/*   Updated: 2021/09/30 15:34:49 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*get_env_val(char *to_find, char **env)
{
	int		i;
	int		l_to_find;
	char	*new;

	i = 0;
	l_to_find = ms_strlen(to_find);
	while (!ms_strnstr(env[i], to_find, l_to_find))
		i++;
	new = ms_strdup(env[i] + l_to_find + 1);
	return (new);
}
