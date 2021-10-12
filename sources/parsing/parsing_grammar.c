//
// Created by Antoine LANGLOIS on 05/10/2021.
//

#include "parsing.h"
/*
t_node *parse_simple_command(t_simple_command **list)
{
	t_simple_command *cur;
	t_node **root;

	if (!list)
		return (NULL);
	*root = new_node(root, list);
	if (!node)
		return (NULL);
	cur = *list;
	while (ms_strcmp(cur->token[0], "NEWLINE") || cur->next != NULL)
	{
		new_node(root, cur);
		cur = cur->next;
	}
	return (node);
}
*/
void io_redirections(t_command *cmd)
{
	t_simple_command **lst;

	lst = cmd->list;
	while (*lst != NULL)
	{
		if ((*lst)->token == WORD)
		{
			if ((*lst)->next->token == PIPE)
				*lst = (*lst)->next;
			if ((*lst)->next->token == GREAT)
			{
				free(cmd->out_file);
				cmd->out_file = NULL;
				cmd->out_file = ms_strdup((*lst)->next->next->arg[0]);
			}
			if ((*lst)->next->token == LESS)
			{
				free(cmd->in_file);
				cmd->in_file = NULL;
				cmd->in_file = ms_strdup((*lst)->next->next->arg[0]);
			}
		}
		*lst = (*lst)->next;
	}
}

int	parser(t_command *cmd)
{
	io_redirections(cmd);
	//node = parse_simple_command(cmd->list);
	print_command(cmd);
	return (0);
}