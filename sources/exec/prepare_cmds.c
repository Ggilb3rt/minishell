/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 11:12:42 by ggilbert          #+#    #+#             */
/*   Updated: 2021/10/29 14:04:18 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//ret = {{"ls", "la"}, {"cd"}, {"grep", "poeut"}}
//char ** == {"ls", "la"}
// char * == "ls"
char	***pass_cmds_to_exec(t_command *cmds)
{
	t_simple_command	*cur;
	int					i;
	int					count;
	int					arr_size;
	char				***ret;

	arr_size = 0;
	count = 0;
	cur = *cmds->list;
	ret = malloc(sizeof(ret) * (cmds->numb_simple_commands));
	while (cur != NULL)
	{
		i = 0;
		arr_size = array_size(cur->arg) + 1;
		printf("arr_size %d\n", arr_size);
		while (i < arr_size)
		{
			printf("%d, %s ; ", i, cur->arg[i]);
			i++;
		}
		printf("\n");
		cur = cur->next;
		count++;
	}
	return (ret);
}

int	check_access(char *path, int *fd)
{
	if (access(path, F_OK | R_OK) == -1)
	{
		*fd = -1;
		perror("access");
		return (0);
	}
	*fd = open(path, O_RDONLY);
	printf("check fd in access in file %d\n", *fd);
	return (1);
}

/*
* L'acces, la creation et le append sur les fichiers fonctionnent
*/
int	associate_file_to_cmd(t_simple_command **list)
{
	t_simple_command	*cur;
	int					cur_token;
	int					tmp_fd;

	cur = *list;
	tmp_fd = 0;
	while (cur != NULL)
	{
		cur_token = cur->token;
		if (cur_token == GREAT || cur_token == DGREAT
			|| cur_token == LESS || cur_token == DLESS)
		{
			cur = cur->next;
			if (cur->token != WORD)
				return (-1);
			if (cur_token == LESS)
			{
				if (!check_access(cur->arg[0], &tmp_fd))
					return (-1);
			}
			else if (cur_token == GREAT)
				tmp_fd = open(cur->arg[0], O_CREAT | O_WRONLY, 0666);
			else if (cur_token == DGREAT)
				tmp_fd = open(cur->arg[0], O_CREAT | O_WRONLY | O_APPEND, 0666);
			else if (cur_token == DLESS)
				tmp_fd = 1;
			if (tmp_fd == -1)
			{
				perror("open");
				return (errno);
			}
			if (tmp_fd > 0)
				write(tmp_fd, "Loeut\n", 7);
			printf("tmp fd : %d\n", tmp_fd);
		}
		cur = cur->next;
	}
	return (0);
}

int	associate_file_to_cmd2(t_command *cmds)
{
	t_simple_command	*cur;
	int					cur_token;
	int					tmp_fd;

	cur = cmds->list[0];
	tmp_fd = 0;
	while (cur != NULL)
	{
		cur_token = cur->token;
		if (cur_token == GREAT || cur_token == DGREAT
			|| cur_token == LESS || cur_token == DLESS)
		{
			cur = cur->next;
			if (cur->token != WORD)
				return (-1);
			/*
			if (cur_token == LESS)
			{
				if (!check_access(cur->arg[0], &cmds->fd_in))
					return (-1);
			}
			else if (cur_token == GREAT)
				cmds->fd_out = open(cur->arg[0], O_CREAT | O_WRONLY, 0666);
			else if (cur_token == DGREAT)
				cmds->fd_out = open(cur->arg[0], O_CREAT | O_WRONLY | O_APPEND, 0666);
			else if (cur_token == DLESS)
				tmp_fd = 1;
			*/
			 if (tmp_fd == -1)
			{
				perror("open");
				return (errno);
			}
			//if (tmp_fd > 0)
			//	write(tmp_fd, "Loeut\n", 7);
			//printf("tmp fd : %d\n", tmp_fd);
		}
		cur = cur->next;
	}
	return (0);
}