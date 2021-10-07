//
// Created by Antoine LANGLOIS on 05/10/2021.
//

#include "parsing.h"



t_command parse_simple_command(t_simple_command **list)
{
	t_simple_command *cur;
	t_node **root;

	if (!list)
		return (NULL);
	root = new_node(root, list);
	if (!node)
		return (NULL);
	cur = *list;
	while (ms_strcmp(cur->token[0], "NEWLINE") || cur->next != NULL)
	{
		//set_node_val_str(word, tok->text);
		//add_child_node(node, word);
		cur = cur->next;
	}
	return (node);
}

int	parser(t_simple_command **list)
{
	t_node *node;

	node = parse_simple_command(list);
}