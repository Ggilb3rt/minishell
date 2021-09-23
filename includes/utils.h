//
// Created by Antoine LANGLOIS on 22/09/2021.
//

#ifndef MINISHELL_UTILS_H
# define MINISHELL_UTILS_H

# include "minishell.h"

/* utils 1 (some libft functions) */
int		ms_strlen(const char *str);
int		ms_strcmp(const char *s1, const char *s2);

/* utils 2
 * split
 */
int		ms_split(char const *s, char c);

/* utils 3
 * handling errors
 * frees
 */
void 	free_tab(char **tab);

#endif
