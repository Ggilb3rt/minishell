//
// Created by Antoine LANGLOIS on 24/09/2021.
//

#ifndef MINISHELL_ENV_H
#define MINISHELL_ENV_H

# include "minishell.h"

#endif //MINISHELL_ENV_H

typedef struct s_list_envp
{
	char				*content;
	struct s_list_envp	*next;
}	t_list_envp;

// Env list edit
void		edit_lst_content(t_list_envp *env, int index, char *new_val);
void		ms_lst_push_end(t_list_envp **alst, t_list_envp *new);
void		remove_lst_content(char *content);
int			ms_lst_pop_end(t_list_envp *head);
void		ms_lst_free_all(t_list_envp *head);

void		print_envp(t_list_envp *head);
t_list_envp	*new_char_list(char *str);
t_list_envp	*create_msenvp_lst(char **envp);
