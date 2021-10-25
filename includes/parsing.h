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


// ? ajouter un define FILE qui correspond a un WORD mais apres un LESS GREAT etc
# define ERROR 0
# define WORD 1
# define LESS 2
# define GREAT 3
# define DLESS 4
# define DGREAT 5
# define PIPE 6
# define NWLINE 7

/*
* Add in_file_fd and out_file_fd
* ls > out > out2 > out3 est valide, tout les fichiers sont créés
* mais seulement out3 contient le retour de ls
*/
typedef struct s_to_exec_cmd
{
	char		**arg;
	int			in_file_fd;
	int			out_file_fd;
}				t_to_exec_cmd;



typedef struct s_split
{
	int 	size;
	int		count;
	int 	count_s;
	int 	count_d;
	int		len;
	int		open;
}				t_split;

/*
typedef struct s_node
{
	char 			**type;
	int				children;
	struct s_node	*first_child;
	struct s_node	*next_sibling;
	struct s_node	*prev_sibling;
}				t_node;
*/

/* parsing main */
int					lexer_and_parser(char *str, t_command *cmd);
//int				convert(t_simple_command **list, char **arg, int i, int cur);

/* parsing tokens */
int					create_token(char *str);

/* parsing element */
void 				add_elem(t_simple_command *new, t_simple_command **list_arg);
t_simple_command	*alloc_elem(char **str);
void 				add_newline(t_simple_command **list, char **arg, int i);

/* parsing grammar */
int					parser(t_command *cmd);

/* parsing lexer */
t_simple_command	**lexer(char **new);

/* parsing split 1 */
char				**split_quote(char *str);

/* parsing split 2 */
int					word_count(char *str);
char				*split_words(char *str, int strt, int fnsh);

/* debug */
int					print_simple_command(t_simple_command **sc);
int					print_command(t_command *cmd);

#endif
