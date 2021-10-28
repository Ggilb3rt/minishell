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
# include <errno.h>

# define UINT_MAX 4294967294
# define QEXIT 0
# define QERROR 1
# define HERE 2

typedef struct s_simple_command
{
	int 					numb_avail;
	int 					numb;
	char 					**arg;
	int						token;
	struct s_simple_command	*next;
	//simple_command();
	//void insert_argument(char *argument);
}				t_simple_command;

/*
 * Describes a complete command with the multiple pipes if any and
 * input/output redirection if any.
 */

typedef struct s_command
{
	int 					numb_avail_simple_commands;
	int 					numb_simple_commands;
	t_simple_command		**list;
	char 					*out_file;
	char 					*in_file;
	char 					*err_file;
	int 					fd;
	char 					*heredoc;
	struct s_command 		*pipe_out;
	struct s_command 		*pipe_in;
	struct s_command		*next;
	//void prompt();
	//void print();
	//void execute();
	//void clear();
	//command();
	//void insert_simple_command(simple_command * simple_command);
	//static t_command		cur_command;
	//static t_simple_command	*cur_simple_command;
}				t_command;

# include "parsing.h"
# include "history.h"
# include "ms_env.h"
# include "builtins.h"
# include "utils.h"
# include "exec.h"
# include "flux.h"
# include "heredoc.h"

#endif