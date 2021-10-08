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
	new = malloc(sizeof(char *) * size + 1);
	if (!new)
		return (NULL);
	while (str[i])
	{
		if (!ms_strcmp(str[i], ">"))
			new[i] = ms_strdup("GREAT");
		else if (!ms_strcmp(str[i], "<"))
			new[i] = ms_strdup("LESS");
		else if (!ms_strcmp(str[i], ">>"))
			new[i] = ms_strdup("DGREAT");
		else if (!ms_strcmp(str[i], "<<"))
			new[i] = ms_strdup("DLESS");
		else if (!ms_strcmp(str[i], "|"))
			new[i] = ms_strdup("PIPE");
		else if (ms_is_alpha(str[i]))
			new[i] = ms_strdup("WORD");
		else if (!ms_strcmp(str[i], "/"))
			new[i] = ms_strdup("NEWLINE");
		else
			new[i] = ms_strdup("ERROR");
		i++;
	}
	new[i] = NULL;
	return (new);
}

static char	**get_arg(char **str, int i, int last)
{
	char	**new;
	int		diff;
	int		j;

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

int	convert(t_simple_command **list, char **arg, int i, int cur)
{
	char 				**new;
	t_simple_command	*elem;

	if (cur != 0)
		cur++;
	new = get_arg(arg, i, cur);
	elem = alloc_elem(new);
	add_elem(elem, list);
	if (arg[i] != NULL)
	{
		cur = i;
		new = get_arg(arg, i + 1, cur);
		elem = alloc_elem(new);
		add_elem(elem, list);
	}
	return (cur);
}

t_simple_command **lexer(char **arg)
{
	t_simple_command	*cmd;
	int					i;
	int 				cur;

	i = 0;
	cur = 0;
	list = malloc(sizeof(t_simple_command *));
	if (!list)
		return (NULL);
	while (arg[i])
	{
		if (!ms_strcmp(arg[i], "<") || !ms_strcmp(arg[i], ">") || !ms_strcmp(arg[i], "|")
			|| !ms_strcmp(arg[i], "<<") || !ms_strcmp(arg[i], ">>"))
			cur = convert(list, arg, i, cur);
		i++;
	}
	if (i - cur > 0)
		cur = convert(list, arg, i, cur);
	add_newline(list, arg, i);
	print_simple_command(list);
	return (list);
}

int		get_line(char *str)
{
	t_command	*cmd;
	char		**arg;

	arg = ms_split(str, ' ');
	cmd->list = lexer(arg);
	parser(cmd->list);
	return (1);
}