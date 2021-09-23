//
// Created by Antoine LANGLOIS on 22/09/2021.
//

#include "commands.h"

/* unset with no options or arguments : unset 'name'
 * - Unset values and attributes of variables and functions
 * each variable of function specified by name shall be unset.
 * Unsetting a variable or function that was not previously set shall not be considered an error and does not
 * cause the shell to abort.
 * NOTE : VARIABLE= is equivalent to VARIABLE=""
 */