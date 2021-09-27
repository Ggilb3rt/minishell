//
// Created by Antoine LANGLOIS on 22/09/2021.
//

#ifndef MINISHELL_PARSING_H
# define MINISHELL_PARSING_H

# include "minishell.h"

/*
 * Command Data Structure (see notes.txt)
 * Describes a simple command and arguments
 * numb_avail_arg = available space for arguments currently preallocated
 * numb_arg = number of arguments
 * arg = array of arguments
 */

typedef struct s_simple_command
{
	int 					numb_avail;
	int 					numb;
	char 					**arg;
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
	t_simple_command		**simple_command;
	char 					*out_file;
	char 					*in_file;
	char 					*err_file;
	int 					background;
	//void prompt();
	//void print();
	//void execute();
	//void clear();
	//command();
	//void insert_simple_command(simple_command * simple_command);
	//static t_command		cur_command;
	//static t_simple_command	*cur_simple_command;
}				t_command;

int 	parse_line(char *str);

/* debug */
int print_simple_command(t_simple_command *sc);

#endif
