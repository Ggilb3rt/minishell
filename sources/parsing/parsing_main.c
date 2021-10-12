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

static int  go_next_quote(char *str, int i)
{
	while (str[i] != '\"')
	{
		if (str[i] == '\0')
			return (0);
		i++;
	}
	return (i);
}

static int 	word_count(char *str)
{
	int	nb_words;
	int	trig;

	nb_words = 0;
	trig = 0;
	while (str[i])
	{
		if (str[i] == '\"')
		{
			i += go_next_quote(str, i);
		}
		if (str[i] != ' ' && trig == 0)
		{
			trig = 1;
			nb_words++;
		}
		else if (str[i] == ' ')
			trig = 0;
		str++;
	}
	printf("NBWORD = %d\n", nb_words);
	return (nb_words);
}

static char **ms_split_quote(char *str)
{
	printf("STR = %s\n", str);
	int	i;
	char 	**new;
	int 	size;

	size = word_count(str);
	(void)i;
	(void)size;
	new = NULL;
	return (new);
}

int		lexer_and_parser(char *str, t_command *cmd)
{
	char		**arg;
	//int 		ret;

	(void)cmd;
	arg = ms_split_quote(str);
	/*
	cmd->list = lexer(arg);
	if (!cmd->list)
	{
		printf("Error input string\n");
		exit (0);
	}
	ret = parser(cmd);
	if (!ret)
	{
		printf("Error synthax\n");
		exit (0);
	}
	 */
	return (1);
}