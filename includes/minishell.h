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
# include <sys/wait.h>
# include <sys/uio.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>

# define UINT_MAX 4294967294
# define QEXIT 0
# define EHERE 1
# define QHERE 2

# define IN 0
# define OUT 1

typedef struct s_simple_command
{
	int						numb_avail;
	int						numb;
	char					**arg;
	int						token;
	struct s_simple_command	*next;
}				t_simple_command;

typedef struct s_command
{
	int						numb_avail_simple_commands;
	int						numb_simple_commands;
	t_simple_command		**list;
	char 					*out_file;
	char 					*in_file;
	char 					*err_file;
	int 					fd_in;
	int 					fd_out;
	char 					*end;
	struct s_command		*next;
}				t_command;

extern int	g_ret;

# include "parsing.h"
# include "env.h"
# include "builtins.h"
# include "utils.h"
# include "exec.h"
# include "heredoc.h"
# include "libft.h"

void sig_handler(int n);

#endif