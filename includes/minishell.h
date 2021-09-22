//123

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "history.h"

/* utils 1 */
int ms_strcmp(const char *s1, const char *s2);
//ms_strlen

#endif