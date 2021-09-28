//
// Created by Antoine LANGLOIS on 22/09/2021.
//

#ifndef MINISHELL_UTILS_H
# define MINISHELL_UTILS_H

# include "minishell.h"

/* utils 1 (some libft functions) */
size_t	ms_strlen(const char *str);
int		ms_strcmp(const char *s1, const char *s2);
char 	*ms_strdup(const char *str);
int 	ms_is_alpha(const char *str);

/* utils 2
 * split
 */
char 	**ms_split(const char *s, char c);

/* utils 3
 * array count
 */
int 	array_size(char **arr);

/* utils 4
 * handling errors
 * frees
 */
void 	free_tab(char **arr);

#endif
