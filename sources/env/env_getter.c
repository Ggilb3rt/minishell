/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_getter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 14:36:36 by ggilbert          #+#    #+#             */
/*   Updated: 2021/11/02 16:41:44 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/*
! To avoid errors maybe to add function to check if "to_find"
! has '=' at the end (if he don't add it ?)

* ex :
	if I add 
		POUETPOUET=pouet
		POUET=lol
	get_ms_env_index("POUET", ms_env) will return the first one but it's an error

	cf to_find_sanitize
*/

char	*to_find_sanitize(char *to_find)
{
	int		len;

	len = ms_strlen(to_find);
	if (to_find[--len] == '=')
		return (ms_strjoin(to_find, ""));
	else
		return (ms_strjoin(to_find, "="));
}

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

	index = -1;
	tmp = ms_env;
	to_find = to_find_sanitize(to_find);
	if (!to_find)
		return (-1);
	len_ms_env = get_ms_env_len(tmp);
	len_to_find = ms_strlen(to_find);
	while (++index < (int)len_ms_env)
	{
		if (ms_strnstr(tmp->content, to_find, len_to_find))
			break ;
		tmp = tmp->next;
	}
	free(to_find);
	if (index == (int)len_ms_env)
		return (-1);
	return (index);
}

char	*get_ms_env_val(char *to_find, t_list_envp *ms_env)
{
	int			i;
	size_t		len_to_find;
	t_list_envp	*tmp;

	tmp = ms_env;
	i = get_ms_env_index(to_find, tmp);
	if (i < 0)
		return (NULL);
	len_to_find = ms_strlen(to_find);
	while (i-- > 0)
		tmp = tmp->next;
	return ((tmp->content) + len_to_find);
}

t_list_envp	*ms_lst_point(int index, t_list_envp *ms_env)
{
	t_list_envp	*tmp;

	tmp = ms_env;
	if (index < 0)
		return (NULL);
	while (index-- > 0)
		tmp = tmp->next;
	return (tmp);
}

/*
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
*/
