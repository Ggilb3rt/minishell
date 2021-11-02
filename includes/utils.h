//
// Created by Antoine LANGLOIS on 22/09/2021.
//

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

/*
 * utils 1 (some libft functions)
 */
size_t		ms_strlen(const char *str);
int			ms_strcmp(const char *s1, const char *s2);
char		*ms_strdup(const char *str);
int			ms_is_alpha(const char *str);
char		*ms_strnstr(const char *haystack, const char *needle, size_t len);

/* utils 1 (some libft functions) */
size_t		ms_strlen(const char *str);
int			ms_strcmp(const char *s1, const char *s2);
char		*ms_strdup(const char *str);
int			ms_is_alpha(const char *str);
char		*ms_strnstr(const char *haystack, const char *needle, size_t len);

/*
 * utils 2
 * split and join
 */
char		**ms_split(const char *s, char c);
char		*ms_strjoin(char const *s1, char const *s2);

/*
 * utils 3
 * array count
 */

int			array_size(char **arr);
int			arr_int_size(int *arr);

/*
 * utils 4
 * handling errors
 * frees
 */
void		free_tab(char **arr);
//void	free_command(t_command *cmd);
//void 	free_simple_command(t_simple_command **list);

/*
 * utils_chr
 */
int			ft_isdigit(int c);
int			ft_isalpha(int c);
int			ft_isalnum(int c);
int			ms_str_isalnum_under(char *s);
char		*ms_strchr(const char *s, int c);

/*
 * From libft
 */
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
char		*ft_strtrim(char const *s1, char const *set);

#endif
