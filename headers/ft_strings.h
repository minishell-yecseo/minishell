#ifndef FT_STRINGS_H
# define FT_STRINGS_H

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

char		**ft_split(char const *s, char c);
int			ft_isalpha(int c);
int			ft_isdigit(int c);

int			ft_strlen(const char *str);
char		*ft_strstr(char *str, char *to_find);
char		*ft_strchr(const char *s, int c);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strdup(const char *s1);
char		*ft_strjoin(char const *s1, char const *s2);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
int			ft_strcmp(char *s1, char *s2);
void		ft_strcpy(char *dst, const char *src);
void		ft_strncpy(char *dest, const char *src, size_t len);
size_t		ft_strlcpy(char *dest, const char *src, size_t destsize);

#endif
