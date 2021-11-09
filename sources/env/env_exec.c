/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 17:24:49 by ggilbert          #+#    #+#             */
/*   Updated: 2021/11/09 17:25:56 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**convert_envplst_to_tab(t_list_envp *ms_env)
{
	char	**tmp_env;
	size_t	len_ms_env;
	size_t	i;

	len_ms_env = get_ms_env_len(ms_env);
	tmp_env = malloc(sizeof(char *) + (len_ms_env + 1));
	if (!tmp_env)
		return (NULL);
	i = 0;
	while (i < len_ms_env)
	{
		tmp_env[i] = ms_strdup(ms_env->content);
		ms_env = ms_env->next;
		i++;
	}
	tmp_env[i] = NULL;
	// int j = 0;
	// while(tmp_env[j] != NULL)
	// {
	// 	printf("convertion envp %d %s\n", j, tmp_env[j]);
	// 	j++;
	// }
	// printf("len %ld, i %ld\n", len_ms_env, i);
	return (tmp_env);
}
