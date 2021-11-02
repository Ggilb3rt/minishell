//
// Created by Antoine LANGLOIS on 01/11/2021.
//

#include "minishell.h"

void cleanup(char **str)
{
	char	*s;
	int 	i;

	i = 0;
	s = *str;
	while (s[i])
	{

		i++;
	}
}