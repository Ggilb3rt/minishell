//
// Created by Antoine LANGLOIS on 24/09/2021.
//

#include "utils.h"

int 	array_size(char **arr)
{
	int i;

	i = 0;
	if (!arr)
		return (0);
	while (arr[i])
		i++;
	return (i);
}