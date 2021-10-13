//
// Created by Antoine LANGLOIS on 13/10/2021.
//

#include "minishell.h"

static int  go_next_quote(char *str, int i)
{
	while (str[i] != '\"')
	{
		printf("[%i][%c]\n", i, str[i]);
		if (str[i] == '\0')
			return (0);
		i++;
	}
	return (i);
}

static int 	meet_quote(char *str, int i, int open)
{
	int jmp;

	jmp = 0;
	i++;
	if (open && ((jmp = go_next_quote(str, i)) > 0))
	{
		i = jmp;
		open = 0;
	}
	else
	{
		printf("error next quote\n");
	}
	return (i);
}

static int 	word_count(char *str)
{
	int	nb_words;
	int	trig;
	int i;
	int open;

	open = 0;
	i = 0;
	nb_words = 0;
	trig = 0;
	while (str[i])
	{
		if (str[i] == '\"')
		{
			if (open == 0 )
				open = 1;
			i = meet_quote(str, i, open);
			if (ms_is_alpha(&str[i + 1]))
				nb_words++;
		}
		if ((str[i] != ' ' && str[i] != '\"') && trig == 0)
		{
			trig = 1;
			nb_words++;
		}
		else if (str[i] == ' ' || str[i] == '\"')
			trig = 0;
		i++;
	}
	return (nb_words);
}

static char *split_words(char *str, int strt, int fnsh)
{
	char *word;
	int i;

	i = 0;
	word = malloc((fnsh - strt + 1) * sizeof(char));
	while (strt < fnsh)
	{
		word[i] = str[strt];
		i++;
		strt++;
	}
	word[i] = '\0';
	return (word);
}

char **split_quote(char *str)
{
	int		i;
	int 	j;
	char 	**new;
	int 	size;
	int		count;
	int		len;
	int		open;
	char	*temp;

	temp = NULL;
	open = 0;
	i = 0;
	j = 0;
	(void)j;
	if (!str)
		return (NULL);
	size = word_count(str);
	len = ms_strlen(str);
	printf("SIZE = %i\n", size);
	new = malloc(sizeof(char *) * size + 1);
	if (!new)
		return (NULL);
	count = -1;
	while (i <= len)
	{
		printf("%c %i", str[i], (str[i] != ' ') && count < 0 && !open);
		printf(" %i", (str[i] == ' ' || str[i] == '\"' || i == len) && count >= 0 && open);
		if ((str[i] != ' ') && count < 0 && !open)
		{
			open = 1;
			count = i;
		}
		else if ((str[i] == ' ' || str[i] == '\"' || i == len) && count >= 0 && open)
		{
			new[j] = split_words(str, count, i);
			if (!ms_strcmp(new[j], " "))
			{
				temp = ms_strjoin(new[j - 1], new[j]);
				free(new[j]);
				free(new[j - 1]);
				new[j - 1] = temp;
				j--;
			}
			count = -1;
			j++;
			if (str[i] == '\"' && open == 1)
			{
				open = 1;
				count = i;
			}
			else
				open = 0;
		}
		printf(" %i",(str[i] != '\"') && count < 0 && !open);
		printf(" %i\n",(str[i] == '\"') && count >= 0 && open);
		if ((str[i] != '\"') && count < 0 && !open)
		{
			open = 1;
			count = i;
		}
		else if ((str[i] == '\"') && count >= 0 && open) {
			i++;
			i = go_next_quote(str, i);
			printf("I = %i, COUNT = %i\n", i, count);
			new[j] = split_words(str, count, i + 1);
			if (ms_strcmp(new[j], "\"") || ms_strcmp(new[j], ""))
			{
				free(new[j]);
				j--;
			}
			count = -1;
			j++;
			if (ms_is_alpha(&str[i + 1]))
			{
				i++;
				open = 1;
				count = i;
			}
			else if (str[i + 1] == ' ')
			{
				open = 1;
				count = i;
			}

		}
		i++;
	}
	new[j] = 0;
	return (new);
}