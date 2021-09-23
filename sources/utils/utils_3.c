//
// Created by Antoine LANGLOIS on 23/09/2021.
//

#include "utils.h"

void 	free_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
}