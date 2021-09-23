//
// Created by Antoine LANGLOIS on 22/09/2021.
//

#ifndef MINISHELL_COMMANDS_H
# define MINISHELL_COMMANDS_H

# include "minishell.h"

/* echo with option -n : echo 'string' */

/* cd with only a relative or absolute path */

/* pwd with no options */

/* export with no options : export 'name'='word' */

/* unset with no options or arguments : unset 'name' */

/* env with no options or arguments : env 'NAME'='value' */

/* exit with no options : exit 'n' */
int    cmd_exit(char *line);

#endif