//
// Created by Antoine LANGLOIS on 22/09/2021.
//

#include "history.h"

/* external functions that we may use :
 * - void add_history(const char *string) : Place string at the end of the history list. The associated
 * data field (if any) is set to NULL.
 * - void rl_clear_history(void) : Clear the history list by deleting all of the entries, in the same
 * manner as the History library's 'clear_history()' function. This differs from 'clear_history' because it
 * frees private data Readline saves in the history list.
 */

/* using_history : initialise history
 * - create file
 * - ...
 */

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

/* clear_history or free_history_entry : remove and free history
 * use of the rl_clear_history function
 */