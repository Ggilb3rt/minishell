//
// Created by Antoine LANGLOIS on 02/11/2021.
//

#ifndef MINISHELL_LIBFT_H
# define MINISHELL_LIBFT_H

# include "minishell.h"

size_t		ft_strlen(const char *str);
int 		ft_strcmp(const char *s1, const char *s2);
char 		*ft_strdup(const char *str);
int 		ft_isalpha(int c);
int 		ft_isalnum(int c);
int 		ft_str_isalnum_under(char *s);
int 		ft_isdigit(int c);
char 		**ft_split(const char *s, char c);
char 		*ft_strjoin(const char *s1, const char *s2);
size_t		ft_strlcpy(char *dst, const char *srv, size_t dstsize);
char 		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char 		*ft_strtrim(const char *s1, const char *set);
char 		*ft_substr(const char *s, unsigned int start, size_t len);
char		*ft_strchr(const char *s, int c);

#endif //MINISHELL_LIBFT_H
