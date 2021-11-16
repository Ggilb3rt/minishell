//
// Created by Antoine LANGLOIS on 24/09/2021.
//

#ifndef MS_ENV_H
# define MS_ENV_H

# include "minishell.h"

typedef struct s_list_envp
{
	char				*content;
	struct s_list_envp	*next;
}	t_list_envp;

// env_exec
char		**convert_envplst_to_tab(t_list_envp *ms_env);
char		**convert(t_list_envp *ms_env);

// env_edit
void		edit_lst_content(t_list_envp *env, int index, char *new_val);
void		ms_lst_push_end(t_list_envp **alst, t_list_envp *new);
int			ms_lst_pop_end(t_list_envp *head);
void		ms_lst_pop_inside(t_list_envp *current, t_list_envp *prev);
t_list_envp	*ms_lst_pop_first(t_list_envp *head);

// env_free
void		remove_lst_content(char *content);
void		ms_lst_free_all(t_list_envp *head);

// env
void		print_envp(t_list_envp *head);
t_list_envp	*new_char_list(char *str);
t_list_envp	*create_msenvp_lst(char **envp);

//env var
void		convert_var(t_command **command);

#endif
