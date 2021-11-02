//
// Created by Antoine LANGLOIS on 02/11/2021.
//

#include "minishell.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (*str++)
		i++;
	return (i);
}