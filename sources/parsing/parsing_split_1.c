//
// Created by Antoine LANGLOIS on 13/10/2021.
//

#include "minishell.h"

static void init_split(t_split *splt, char *str)
{
	splt->open = 0;
	splt->count = -1;
	splt->count_s = -1;
	splt->count_d = -1;
	splt->size = word_count(str);
	splt->len = ms_strlen(str);
}

static void open_quote(char *str, int i, t_split *splt)
{
	if (str[i] == '\'')
	{
		splt->count_s = i;
		splt->open = 1;
	}
	else if (str[i] == '\"')
	{
		splt->count_d = i;
		splt->open = 2;
	}
}

static char *create_tab(char *str, int i, t_split *splt)
{
	if ((str[i] == '\"' || str[i] == '\'') && splt->open == 0 && splt->count < 0)
		open_quote(str, i, splt);
	else if (splt->open == 0 && str[i] != ' ' && splt->count < 0)
		splt->count = i;
	else if (((str[i] == '\"' && splt->count_d >= 0)
			  || (str[i] == '\'' && splt->count_s >= 0))
			 && splt->open)
	{
		if (splt->count_s > 0)
			return(split_words(str, splt->count_s, i + 1));
		else if (splt->count_d > 0)
			return(split_words(str, splt->count_d, i + 1));
	}
	else if ((str[i] == ' ' || i == splt->len || str[i] == '\"')
			 && splt->open == 0 && splt->count >= 0)
		return(split_words(str, splt->count, i));
	return (NULL);
}

char **split_quote(char *str)
{
	int		i;
	int 	j;
	char 	**new;
	t_split	*splt;

	splt = malloc(sizeof(t_split));
	init_split(splt, str);
	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	new = malloc(sizeof(char *) * splt->size + 1);
	if (!new)
		return (NULL);
	while (i <= splt->len)
	{
		/*
		if ((str[i] == '\"' || str[i] == '\'') && splt->open == 0 && splt->count < 0)
		{
			open_quote(str, i, splt);
		}
		else if (splt->open == 0 && str[i] != ' ' && splt->count < 0)
		{
			splt->count = i;
		}
		else if (((str[i] == '\"' && splt->count_d >= 0)
			|| (str[i] == '\'' && splt->count_s >= 0))
			&& splt->open)
		{
			if (splt->count_s > 0)
			{
				new[j] = split_words(str, splt->count_s, i + 1);
				splt->count_s = -1;
			}
			else if (splt->count_d > 0)
			{
				new[j] = split_words(str, splt->count_d, i + 1);
				splt->count_d = -1;
			}
			j++;
			splt->open = 0;
		}
		else if ((str[i] == ' ' || i == splt->len || str[i] == '\"')
				 && splt->open == 0 && splt->count >= 0)
		{
			new[j] = split_words(str, splt->count, i);
			splt->count = -1;
			j++;
			if ((str[i] == '\"' || str[i] == '\'') && splt->open == 0 && splt->count < 0)
			{
				open_quote(str, i, splt);
			}
		}
		*/
		new[j] = create_tab(str, i, splt);
		if (new[j])
		{
			//if (splt->count >= 0)
			//{
				if ((str[i] == '\"' || str[i] == '\'')
				&& splt->open == 0 && splt->count < 0)
					open_quote(str, i, splt);
			//}
			init_split(splt, str);
			j++;
		}
		i++;
	}
	new[j] = 0;
	return (new);
}
