//
// Created by Antoine LANGLOIS on 22/09/2021.
//

#ifndef MINISHELL_UTILS_H
# define MINISHELL_UTILS_H

# include "minishell.h"

/* utils 1 (some libft functions) */
size_t	ms_strlen(const char *str);
int		ms_strcmp(const char *s1, const char *s2);

/* utils 2
 * split
 */
char 	**ms_split(char const *s, char c);

/* utils 3
 * array count
 */
int 	array_count(char **arr);

/* utils 4
 * handling errors
 * frees
 */
void 	free_tab(char **arr);

#endif
