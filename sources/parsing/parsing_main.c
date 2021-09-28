//
// Created by Antoine LANGLOIS on 22/09/2021.
//

#include "minishell.h"

/* these functions will parse the string entered in the prompt
 * they will store all the information we need in a structure declared in the associated header file
 *
 * what we need to know :
 * - the subject specifies that we don't need to interpret unclosed quotes or unspecified special
 * characters
 */
/*
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
*/
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

static t_simple_command *get_symbol(char *str)
{
	t_simple_command *new;

	if (!str)
		return (NULL);
	new = malloc(sizeof(t_simple_command));
	if (!new)
		return (NULL);
	new->arg = &str;
	new->numb = 0;
	new->numb_avail = 0;
	new->token = NULL;
	new->next = NULL;
	return (new);
}

void create_token(t_simple_command **list)
{
	t_simple_command *cur;
	int	size;
	int	i;

	i = 0;
	cur = *list;
	while (cur->next != NULL)
	{
		size = array_size(cur->arg);
		cur->token = malloc(sizeof(char *) * size + 1);
		while (cur->arg[i])
		{
			printf("%s\n", cur->arg[i]);
			if (!ms_strcmp(cur->arg[i], ">"))
				cur->token[i] = ms_strdup("GREAT");
			else if (!ms_strcmp(cur->arg[i], "<"))
				cur->token[i] = ms_strdup("LESS");
			else if (!ms_strcmp(cur->arg[i], ">>"))
				cur->token[i] = ms_strdup("GREATGREAT");
			else if (!ms_strcmp(cur->arg[i], "<<"))
				cur->token[i] = ms_strdup("LESSLESS");
			else if (!ms_strcmp(cur->arg[i], "|"))
				cur->token[i] = ms_strdup("PIPE");
			else if (ms_is_alpha(cur->arg[i]))
				cur->token[i] = ms_strdup("WORD");
			i++;
		}
		cur->token[i] = NULL;
		cur = cur->next;
	}
}

int lexer(char **arg)
{
	t_simple_command	**list;
	char 				**new;
	t_simple_command	*elem;
	int					i;
	int 				last;

	i = 0;
	last = 0;
	new = NULL;
	list = malloc(sizeof(t_simple_command));
	while (arg[i])
	{
		if (!ms_strcmp(arg[i], "<") || !ms_strcmp(arg[i], ">") || !ms_strcmp(arg[i], "|")
			|| !ms_strcmp(arg[i], "<<") || !ms_strcmp(arg[i], ">>"))
		{
			elem = get_symbol(arg[i]);
			insert_command(elem, list);
			new = get_arg(arg, i, last);
			elem = alloc_command(new);
			insert_command(elem, list);
			last = i + 1;
		}
		i++;
	}
	if (i - last > 0)
	{
		new = get_arg(arg, i, 0);
		elem = alloc_command(new);
		insert_command(elem, list);
		new = get_arg(arg, i, last);
		elem = alloc_command(new);
		insert_command(elem, list);
	}
	create_token(list);
	print_simple_command(list);
	return (0);
}

int		parse_line(char *str)
{
	char	**arg;

	arg = ms_split(str, ' ');
	lexer(arg);
	return (1);
}