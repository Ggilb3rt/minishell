//
// Created by Antoine LANGLOIS on 20/10/2021.
//

#ifndef MINISHELL_SIGNALS_H
# define MINISHELL_SIGNALS_H

# include "minishell.h"

# include <signal.h>

typedef struct s_signal
{
	int 		ret;
}				t_signal;

t_signal g_sig;

void ms_signal();

#endif //MINISHELL_SIGNALS_H
