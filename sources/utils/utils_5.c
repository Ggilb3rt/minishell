/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 14:36:36 by ggilbert          #+#    #+#             */
/*   Updated: 2021/10/06 15:13:36 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

size_t	get_ms_env_len(t_list_envp *ms_env)
{
	size_t		i;
	t_list_envp	*tmp;

	i = 0;
	tmp = ms_env;
	while (tmp->next != NULL)
	{
		i++;
		tmp = tmp->next;
	}
	i++;
	return (i);
}

int	get_ms_env_index(char *to_find, t_list_envp *ms_env)
{
	int			index;
	size_t		len_to_find;
	t_list_envp	*tmp;
	size_t		len_ms_env;

	index = 0;
	tmp = ms_env;
	len_ms_env = get_ms_env_len(tmp);
	len_to_find = ms_strlen(to_find);
	while (index < (int)len_ms_env)
	{
		if (ms_strnstr(tmp->content, to_find, len_to_find))
			break ;
		index++;
		tmp = tmp->next;
	}
	if (index == (int)len_ms_env)
		return (-1);
	return (index);
}

char	*get_ms_env_val(char *to_find, t_list_envp *ms_env)
{
	int			i;
	t_list_envp	*tmp;

	tmp = ms_env;
	i = get_ms_env_index(to_find, tmp);
	if (i < 0)
		return (NULL);
	while (i-- > 0)
		tmp = tmp->next;
	return (tmp->content);
}

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
