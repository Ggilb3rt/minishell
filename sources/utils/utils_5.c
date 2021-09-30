/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 14:36:36 by ggilbert          #+#    #+#             */
/*   Updated: 2021/09/30 17:18:51 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*get_env_val(char *to_find, char **env)
{
	int		i;
	int		l_to_find;
	char	*new;

	l_to_find = ms_strlen(to_find);
	i = get_env_index(to_find, env);
	new = ms_strdup(env[i] + l_to_find + 1);
	return (new);
}

int	get_env_index(char *to_find, char **env)
{
	int		i;
	int		l_to_find;

	i = 0;
	l_to_find = ms_strlen(to_find);
	while (!ms_strnstr(env[i], to_find, l_to_find))
		i++;
	return (i);
}
