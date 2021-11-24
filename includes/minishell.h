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
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <limits.h>

# define QEXIT 0
# define EHERE -1
# define QHERE -2

# define IN 0
# define OUT 1

# define BUILT_ECHO 0
# define BUILT_PWD 1
# define BUILT_ENV 2

# define BUILT_CD 10
# define BUILT_EXPORT 11
# define BUILT_UNSET 12
# define BUILT_EXIT 13

typedef struct s_list_envp
{
	char				*content;
	struct s_list_envp	*next;
}	t_list_envp;


typedef struct s_g_sig
{
	int						ret;
	int						quit;
}	t_g_sig;
/*
typedef struct s_simple_command
{
	int						numb_avail;
	int						numb;
	char					**arg;
	int						token;
	int						build;
	struct s_simple_command	*next;
}				t_simple_command;
*/
typedef struct s_command
{
	int						numb_avail_simple_commands; //inutile?
	int						numb_simple_commands; //inutile?
	int 					token; //inutile?
	char					**arg;
	char 					*out_file;
	char 					*in_file;
	char 					*err_file; //inutile?
	int 					fd_in;
	int 					fd_out;
	char 					*end;
	int 					build;
	int						can_exec;
	struct s_command		*next;
}				t_command;

extern t_g_sig	g_ret;

# include "parsing.h"
# include "env.h"
# include "builtins.h"
# include "utils.h"
# include "exec.h"
# include "heredoc.h"
# include "libft.h"

void	sig_handler(int n);

#endif