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
	char					**token;
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
	//void prompt();
	//void print();
	//void execute();
	//void clear();
	//command();
	//void insert_simple_command(simple_command * simple_command);
	//static t_command		cur_command;
	//static t_simple_command	*cur_simple_command;
}				t_command;

typedef struct s_node
{
	char 			**type;
	int				children;
	struct s_node	*first_child;
	struct s_node	*next_sibling;
	struct s_node	*prev_sibling;
};

/* parsing main */
int					get_line(char *str);
char				**create_token(char **str);
int					convert(t_simple_command **list, char **arg, int i, int cur);

/* parsing element */
void 				add_elem(t_simple_command *new, t_simple_command **list_arg);
t_simple_command	*alloc_elem(char **str);
void 				add_newline(t_simple_command **list, char **arg, int i);

/* parsing command */
int					parser(t_simple_command **list);

/* parsing node */
t_node				new_node(t_node **root, t_simple_command **list);

/* debug */
int print_simple_command(t_simple_command **sc);

#endif
