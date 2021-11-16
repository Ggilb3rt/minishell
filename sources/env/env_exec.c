/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 17:24:49 by ggilbert          #+#    #+#             */
/*   Updated: 2021/11/16 16:13:38 by ggilbert         ###   ########.fr       */
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
	tmp_env = malloc(sizeof(ms_env->content) + (len_ms_env + 1));
	if (!tmp_env)
		return (NULL);
	i = 0;
	while (i < len_ms_env)
	{
		tmp_env[i] = ft_strdup(ms_env->content);
		printf("i = %zu, %p, %s, content = %s\n", i, tmp_env[i], tmp_env[i], ms_env->content);
		if (ms_env->next != NULL)
			ms_env = ms_env->next;
		//printf("next content %s\n", ms_env->content);
		i++;
	}
	tmp_env[i] = NULL;
	i = 0;
	while (tmp_env[i] != NULL)
	{
		printf("convertion envp %zu %s\n", i, tmp_env[i]);
		//write(1, tmp_env[j], strlen(tmp_env[j]));
		//write(1, "\n", 1);
		i++;
	}
	printf("len %ld, i %ld\n", len_ms_env, i);
	return (tmp_env);
}

//! la valeur de tmp[i] est bien set au depart mais se fait modifier dans la boucle plus tard...
char **convert(t_list_envp *ms_env)
{
	char		**tmp;
	int			len_ms_env;
	int			i;
	t_list_envp	*cur;

	tmp = NULL;
	cur = ms_env;
	i = 0;
	printf("\ndebut %p\n", cur);
	len_ms_env = get_ms_env_len(cur);
	printf("fin %p, len %d\n\n", cur, len_ms_env);
	print_envp(ms_env);
	tmp = malloc(sizeof(ms_env->content) + (len_ms_env + 1));
	if (tmp == NULL)
		return (NULL);
	while (cur != NULL)
	{
		tmp[i] = ft_strdup(cur->content);
		printf("%p in tmp[0] = %s\n", tmp[0], tmp[0]);
		printf("%p in tmp[%d] = %s\n", tmp[i], i, tmp[i]);
		cur = cur->next;
		i++;
	}
	tmp[i] = NULL;
	printf("in tmp[%d] = %s\n", i, tmp[i]);

	i = 0;
	printf("\nmanuel %s\n\n", tmp[0]);
	while (i < len_ms_env)
	{
		printf("out tmp[%d] = %s\n", i, tmp[i]);
		i++;
	}
	printf("out tmp[%d] = %s\n", i, tmp[i]);
	return (tmp);
}
