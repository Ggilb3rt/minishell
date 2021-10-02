//
// Created by Antoine LANGLOIS on 24/09/2021.
//

#ifndef MINISHELL_ENV_H
#define MINISHELL_ENV_H

# include "minishell.h"

#endif //MINISHELL_ENV_H

typedef struct s_list_envp
{
	char				*content;
	struct s_list_envp	*next;
}	t_list_envp;


void envp_test();