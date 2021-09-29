//
// Created by Antoine LANGLOIS on 22/09/2021.
//

#include "minishell.h"

/* echo with option -n : echo 'string'
 * - echo writes the string entered as an argument on the standard output
 * the option -n don't output the trailing newline
 */

// ! same question than pwd with the fd

int	is_flag(char *str)
{
	if (!str)
		return (0);
	if (ms_strlen(str) == 2)
	{
		if (str[0] == '-' && str[1] == 'n')
			return (1);
	}
	return (0);
}

void	print_words(char **words, int flag)
{
	int		i;
	int		nb_words;

	i = 0;
	nb_words = array_size(words);
	if (flag)
		i++;
	while (i < nb_words)
	{
		printf("%s", words[i]);
		if (i + 1 < nb_words)
			printf(" ");
		i++;
	}
	if (!flag)
		printf("\n");
}

int	cmd_echo(char *str)
{
	int		flag;
	char	**words;

	words = ms_split(str, ' ');
	if (!words)
		return (1);
	flag = is_flag(words[0]);
	print_words(words, flag);
	//printf("USE OF THE ECHO COMMAND : %s", str);
	free_tab(words);
	return (0);
}
