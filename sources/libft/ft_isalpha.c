//
// Created by Antoine LANGLOIS on 02/11/2021.
//

#include "minishell.h"

int	ft_isalpha(int c)
{
	if ((c < 'a' || c > 'z')
		&& (c < 'A' || c > 'Z')
		&& (c != '-') && (c != '/'))
		return (0);
	return (1);
}