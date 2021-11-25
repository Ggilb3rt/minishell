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

/*
typedef struct s_to_exec_cmd
{
	char		**arg;
	int			in_file_fd;
	int			out_file_fd;
}				t_to_exec_cmd;
*/

/*
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
*/

typedef struct s_split
{
	char 	*str;
	int 	i;
	int 	l;
	int 	o;
	int 	q;
	char 	**new;
	int 	open_s;
	int 	open_d;
}				t_split;

/*
typedef struct s_count
{
	int		open;
	int 	words;
	int 	i;
	int 	trig;
}				t_count;
*/

/* parsing main */
int					parsing_main(char *str, t_command **cmd, t_list_envp *ms_env);
int					ret_val(t_split *split);
void				del_spaces(t_split *split);

/* parsing tokens */
int					create_token(char *str);

/* parsing add */
void				add_command(t_command **new, t_command **cmd);
int					add_newline(t_command **list);

/* parsing alloc */
t_command			*alloc_command(char **arg);
int					alloc_word(t_split *split, t_list_envp *ms_env);
int					alloc_arg(t_split *split);

/* parsing init */
void				init_split(t_split *split, char *str);
int					init_arg(t_split *split, t_list_envp *ms_env, t_command **cur);

/* parsing get */
void				get_char(t_split *split);
void 				get_arg(t_split *split, t_command **cur, t_command **cmd);
int 				get_arg_pipe(t_split *split, t_command **cur, t_command **cmd);
int 				get_word_space(t_split *split, t_list_envp *ms_env);

/* parsing quotes */
int					open_quote(t_split *split);
int					close_quote(t_split *split);
void				into_quote(t_split *split, t_list_envp *ms_env);

/* parsing redirections */
void				redirection(t_split *split, t_command *cmd);

/* parsing env */
int					search_var(t_split *split, t_list_envp *ms_env);

/* parsing count */
int 				count_args(char *str, int pos);
int 				count_word(char *str, t_list_envp *ms_env, int pos);

/* debug */
int					print_command(t_command *cmd);
int					print_all(t_command **cmd);

#endif
