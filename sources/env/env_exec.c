/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 17:24:49 by ggilbert          #+#    #+#             */
/*   Updated: 2021/11/17 15:53:41 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**convert_envplst_to_tab(t_list_envp *ms_env)
{
	char		**tmp_env;
	size_t		len_ms_env;
	size_t		i;
	t_list_envp	*cur;

	cur = ms_env;
	len_ms_env = get_ms_env_len(cur);
	tmp_env = malloc(sizeof(cur->content) * (len_ms_env + 1));
	if (!tmp_env)
		return (NULL);
	i = 0;
	while (i < len_ms_env)
	{
		tmp_env[i] = ft_strdup(cur->content);
		if (cur->next != NULL)
			cur = cur->next;
		i++;
	}
	tmp_env[i] = NULL;
	return (tmp_env);
}
	// i = 0;
	// while (tmp_env[i] != NULL)
	// {
	// 	printf("convertion envp %zu %s\n", i, tmp_env[i]);
	// 	i++;
	// }
	// printf("convertion envp %zu %s\n", i, tmp_env[i]);
