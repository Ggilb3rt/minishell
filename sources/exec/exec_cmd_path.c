/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 17:37:53 by ggilbert          #+#    #+#             */
/*   Updated: 2021/10/12 18:33:22 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* ls			==> /bin/ls
* ../ls			==> ../ls
* /usr/bin/ls	==> /usr/bin/ls
*/

int	create_paths_with_cmd(char *cmd, char **splitted_paths)
{
	int		i;
	char	*tmp;
	char	*tmp_cmd;

	i = 0;
	tmp_cmd = ms_strjoin("/", cmd);
	if (tmp_cmd == NULL)
		return (0);
	while (splitted_paths[i] != NULL)
	{
		tmp = ms_strjoin(splitted_paths[i], tmp_cmd);
		if (tmp == NULL)
			return (0);
		if (splitted_paths[i])
		{
			free(splitted_paths[i]);
			splitted_paths[i] = tmp;
		}
		tmp = NULL;
		i++;
	}
	free(tmp_cmd);
	return (1);
}

char	*select_wokring_path(char **splitted_paths, char *cmd)
{
	int		i;
	int		can_access;
	char	*good_path;

	i = 0;
	if (!splitted_paths)
		return (NULL);
	while (splitted_paths[i] != NULL)
	{
		can_access = access(splitted_paths[i], X_OK);
		if (can_access == 0)
		{
			good_path = ms_strdup(splitted_paths[i]);
			free_tab(splitted_paths);
			return (good_path);
		}
		i++;
	}
	if (can_access == -1)
		free_tab(splitted_paths);
	return (cmd);
}

char	*init_cmd_path(char *cmd, char *paths)
{
	char	*working_cmd;
	char	**splitted_paths;

	if (cmd == NULL || ms_strlen(cmd) == 0)
		return (NULL);
	splitted_paths = ms_split(paths, ':');
	if (splitted_paths == NULL)
		return (NULL);
	if (!create_paths_with_cmd(cmd, splitted_paths))
		return (NULL);
	working_cmd = select_wokring_path(splitted_paths, cmd);
	return (working_cmd);
}
