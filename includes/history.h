//
// Created by Antoine LANGLOIS on 22/09/2021.
//

#ifndef MINISHELL_HISTORY_H
#define MINISHELL_HISTORY_H

# include "minishell.h"

typedef struct s_list
{
    char    *line;
    double  timestamp;
}               t_list;

typedef struct s_hist
{
    int     size;

}               t_hist;

/* history functions */
// using_history
// history_get_history_state
// history_list

#endif