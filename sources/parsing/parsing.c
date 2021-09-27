//
// Created by Antoine LANGLOIS on 22/09/2021.
//

#include "parsing.h"

/* these functions will parse the string entered in the prompt
 * they will store all the information we need in a structure declared in the associated header file
 *
 * what we need to know :
 * - the subject specifies that we don't need to interpret unclosed quotes or unspecified special
 * characters
 */

static int 	list_size(t_simple_command *list_arg)
{
	t_simple_command	*cur;
	int 				i;

	i = 0;
	cur = list_arg;
	while (cur->next != NULL)
	{
		i++;
		cur = cur->next;
	}
	return (i);
}

static void 	insert_command(char **str, t_simple_command **list_arg)
{
	t_simple_command	*new;
	t_simple_command	*cur;

	if (!str)
		return ;
	new = malloc(sizeof(t_simple_command));
	if (!new)
		return ;
	(*list_arg)->next = NULL;
	(*list_arg)->arg = str;
	if (!*list_arg)
		*list_arg = new;
	else
	{
		cur = *list_arg;
		while (cur->next != NULL)
			cur = cur->next;
		cur->next = new;
		cur->next->next = NULL;
	}
	(*list_arg)->numb_avail = 0;
	(*list_arg)->numb = list_size(*list_arg);
}

static char	**get_arg(char **str, int i, int last)
{
	char **new;
	int diff;
	int	j;

	j = 0;
	diff = i - last;
	new = malloc(sizeof(char *) * diff + 1);
	while (j < diff)
	{
		new[j] = str[last + j];
		j++;
	}
	new[j] = NULL;
	return (new);
}

int lexer(char **commands)
{
	t_simple_command	*list_arg;
	char 				**new;
	int					i;
	int 				last;

	i = 0;
	last = 0;
	new = NULL;
	list_arg = malloc(sizeof(t_simple_command));
	while (commands[i])
	{
		if (!ms_strcmp(commands[i], "<") || !ms_strcmp(commands[i], ">") || !ms_strcmp(commands[i], "|")
			|| !ms_strcmp(commands[i], "<<") || !ms_strcmp(commands[i], ">>"))
		{
			new = get_arg(commands, i, last);
			last = i;
		}
		if (new)
		{
			insert_command(new, &list_arg);
			new = NULL;
		}
		i++;
	}
	if (i - last > 0)
	{
		new = get_arg(commands, i, last);
		insert_command(new, &list_arg);
		new = NULL;
	}
	print_simple_command(list_arg);
	return (0);
}

int		parse_line(char *str)
{
	char	**commands;
	int		i;

	i = 0;
	commands = ms_split(str, ' ');
	lexer(commands);
	return (1);
}