/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 14:35:46 by alangloi          #+#    #+#             */
/*   Updated: 2021/11/28 16:18:33 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirection(t_split *split, t_command **cur, t_list_envp *ms_env)
{
	int	ret;

	if (split->str[split->i] == '>' && split->str[split->i + 1] != '>')
		ret = redir_great(split, cur, ms_env);
	else if (split->str[split->i] == '>' && split->str[split->i + 1] == '>')
		ret = redir_dgreat(split, cur, ms_env);
	else if (split->str[split->i] == '<' && split->str[split->i + 1] != '<')
		ret = redir_less(split, cur, ms_env);
	else if (split->str[split->i] == '<' && split->str[split->i + 1] == '<')
		ret = redir_dless(split, cur, ms_env);
	if (split->str[split->i] == ' ')
	{
		if (split->new[0] != NULL && ft_strcmp(split->new[0], ""))
		{
			if (!get_word_space(split, ms_env))
				return (0);
		}
		del_spaces(split);
	}
	return (ret);
}
