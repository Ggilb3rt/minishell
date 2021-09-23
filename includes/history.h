//
// Created by Antoine LANGLOIS on 22/09/2021.
//

#ifndef MINISHELL_HISTORY_H
#define MINISHELL_HISTORY_H

# include "minishell.h"

/* for theses two structures, refer to https://linux.die.net/man/3/history */

typedef struct s_hist_entry
{
    char			*line;
    double			timestamp;
    histdata_t		data;
}               t_hist_entry;

typedef struct s_hist_state
{
    t_hist_entry	**entries;	/* Pointer to the entries themsleves. */
    int				size;		/* Number of slots allocated to this array. */
    int				length;		/* Number of elements within this array. */
    int				flags;
	int 			offset;		/* The location pointer within this array. */
}               t_hist_state;

/* history functions */
// using_history
// history_get_history_state
// history_list

#endif