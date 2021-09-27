//123

#ifndef MINISHELL_H
# define MINISHELL_H

# define _GNU_SOURCE
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <stdio.h>
# include <signal.h>
# include <dirent.h>
# include <curses.h>
# include <term.h>
# include <termios.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "history.h"
# include "parsing.h"
# include "commands.h"
# include "utils.h"
# include "exec.h"
# include "flux.h"
# include "env.h"



#endif