//
// Created by Antoine LANGLOIS on 05/10/2021.
//

#include "parsing.h"

t_node	new_node(t_node **root, t_simple_command **list)
{
	t_node *new;

	new = malloc(sizeof(t_node));
	if (!new)
		return (NULL);
	node->type = list->token;
	return (new);
}

void 	add_child_node(t_node *parent, t_node *child)
{
	t_node *sibling;

	if (!parent || !child)
		return ;
	if (!parent->first_child)
		parent->first_child = child;
	else
	{
		sibling = parent->first_child;
		while (sibling->next_sibling)
			sibling = sibling->next_sibling;
		sibling->next_sibling = child;
		child->prev_sibling = sibling;
	}
	parent->children++;
}

