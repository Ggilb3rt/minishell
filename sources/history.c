//
// Created by Antoine LANGLOIS on 22/09/2021.
//

#include "minishell.h"

/* using_history : initialise history
 * - create file
 * - ...
 * /

/* history_get_history_state : get state of history (offset, length, size)
 */

/* history_list : retrieve the history list
 * - print added history in file
 *
    int i = 0;
    while (i < ms_hist->length)
    {
        printf(" %8s  %s\n", ms_list[i]->line, ms_list[i]->timestamp);
        free_history_entry(ms_list[i]);
        i++;
    }
*/