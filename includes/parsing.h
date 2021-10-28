//
// Created by Antoine LANGLOIS on 22/09/2021.
//

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

/*
 * Command Data Structure (see notes.txt)
 * Describes a simple command and arguments
 * numb_avail_arg = available space for arguments currently preallocated
 * numb_arg = number of arguments
 * arg = array of arguments
 */

// ? ajouter un define FILE qui correspond a un WORD mais apres un LESS GREAT etc
// reponse : pour moi il n'y a pas besoin psq c'est a la fin du parsing qu'on choppe
// le nom du fichier et qu'on le stock dans une variable
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
 * reponse : je vais y jeter un oeil
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
	char 	**new;
	int 	j;
}				t_split;

typedef struct s_count
{
	int		open;
	int 	words;
	int 	i;
	int 	trig;
}				t_count;

/* parsing main */
int					lexer_and_parser(char *str, t_command **cmd, int *g_ret);

/* parsing tokens */
int					create_token(char *str);

/* parsing add */
void				add_simple(t_simple_command *new, t_simple_command **list);
void				add_command(t_command *new, t_command **list);
void				add_newline(t_command **list, char **arg, int i);

/* parsing alloc */
t_simple_command	*alloc_simple(char **str);
t_command			*alloc_command(char **arg, int begin, int end);

/* parsing grammar */
int					parser(t_command **cmd, int *g_ret);

/* parsing lexer */
t_command			**lexer(char **arg, t_command **cmd);
t_simple_command	**lexer_2(char **arg, int begin, int end);

/* parsing split 1 */
char				**split_quote(char *str);

/* parsing split 2 */
int					word_count(char *str);
char				*split_words(char *str, int strt, int fnsh);

/* parsing split 3 */
void				open_quote(char *str, int i, t_split *splt);
char				*split_words(char *str, int strt, int fnsh);
void 				count_quote(char *str, int i, t_split *splt);
void 				count_spaces(char *str, int i, t_split *splt);

/* debug */
int					print_simple_command(t_simple_command **sc);
int					print_command(t_command *cmd);
int					print_all(t_command **cmd);

#endif
