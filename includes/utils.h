//
// Created by Antoine LANGLOIS on 22/09/2021.
//

#ifndef MINISHELL_UTILS_H
# define MINISHELL_UTILS_H

# include "minishell.h"

/* utils 1 (some libft functions) */
size_t	ms_strlen(const char *str);
int		ms_strcmp(const char *s1, const char *s2);
char	*ms_strdup(const char *str);
int		ms_is_alpha(const char *str);
char	*ms_strnstr(const char *haystack, const char *needle, size_t len);


/* utils 2
 * split and join
 */
char	**ms_split(const char *s, char c);
char	*ms_strjoin(char const *s1, char const *s2);

/* utils 3
 * array count
 */
int		array_size(char **arr);

/* utils 4
 * handling errors
 * frees
 */
void	free_tab(char **arr);

/* utils 5
 * env handler
 */
char	*get_env_val(char *to_find, char **env);
int		get_env_index(char *to_find, char **env);
char	*get_ms_env_val(char *to_find, t_list_envp *ms_env);
int		get_ms_env_index(char *to_find, t_list_envp *ms_env);

/* utils_chr
 */
int		ft_isdigit(int c);
int		ft_isalpha(int c);
int		ft_isalnum(int c);
char	*ms_strchr(const char *s, int c);

#endif
