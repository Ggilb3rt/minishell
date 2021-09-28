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
	if (!new)
		return (0);
	while (j < diff)
	{
		new[j] = ms_strdup(str[last + j]);
		j++;
	}
	new[j] = NULL;
	return (new);
}

/*
 * convert argument into token, here we have a little problem because when removing the first allocation (ERROR) of
 * new[i], the first value of the array gives a strange output. Problem to solve
 */

char	**create_token(char **str)
{
	char	**new;
	int		size;
	int		i;

	i = 0;
	size = array_size(str);
	new = malloc(sizeof(char) * size + 1);
	if (!new)
		return (NULL);
	while (str[i])
	{
		new[i] = ms_strdup("ERROR");
		if (!ms_strcmp(str[i], ">"))
			new[i] = ms_strdup("GREAT");
		else if (!ms_strcmp(str[i], "<"))
			new[i] = ms_strdup("LESS");
		else if (!ms_strcmp(str[i], ">>"))
			new[i] = ms_strdup("GREATGREAT");
		else if (!ms_strcmp(str[i], "<<"))
			new[i] = ms_strdup("LESSLESS");
		else if (!ms_strcmp(str[i], "|"))
			new[i] = ms_strdup("PIPE");
		else if (ms_is_alpha(str[i]))
			new[i] = ms_strdup("WORD");
		i++;
	}
	new[i] = NULL;
	return (new);
}

/* need to review this algo */

int lexer(char **arg)
{
	t_simple_command	**list;
	char 				**new;
	t_simple_command	*elem;
	int					i;
	int 				last;

	i = 0;
	last = 0;
	list = malloc(sizeof(t_simple_command));
	if (!list)
		return (0);
	while (arg[i])
	{
		if (!ms_strcmp(arg[i], "<") || !ms_strcmp(arg[i], ">") || !ms_strcmp(arg[i], "|")
			|| !ms_strcmp(arg[i], "<<") || !ms_strcmp(arg[i], ">>"))
		{
			new = get_arg(arg, i + 1, last);
			elem = alloc_command(new);
			insert_command(elem, list);
			last = i;
			new = get_arg(arg, i, i);
			elem = alloc_command(new);
			insert_command(elem, list);
			i++;
		}
		i++;
	}
	if (i - last > 0)
	{
		if (!ms_strcmp(arg[i - (i - last)], "<") || !ms_strcmp(arg[i - (i - last)], ">") || !ms_strcmp(arg[i - (i - last)], "|")
			|| !ms_strcmp(arg[i - (i - last)], "<<") || !ms_strcmp(arg[i - (i - last)], ">>"))
		{
			new = get_arg(arg, i, i - last);
			elem = alloc_command(new);
			insert_command(elem, list);
			i++;
		}
		new = get_arg(arg, i, last);
		elem = alloc_command(new);
		insert_command(elem, list);
	}
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