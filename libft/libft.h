/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:34:18 by yecnam            #+#    #+#             */
/*   Updated: 2023/04/18 16:36:02 by yecnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct s_stack_node
{
	char				quote;
	struct s_stack_node	*prev;
	struct s_stack_node	*next;
}		t_stack_node;

typedef struct s_stack
{
	struct s_stack_node	*top;
	int					size;
}		t_stack;

void			*ft_calloc(size_t count, size_t size);
void			ft_bzero(void *s, size_t n);
char			**ft_split(char const *s, char c);
int				ft_isalpha(int c);
int				ft_isdigit(int c);

int				ft_strlen(const char *str);
char			*ft_strstr(char *str, char *to_find);
char			*ft_strchr(const char *s, int c);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strdup(const char *s1);
char			*ft_strjoin(char const *s1, char const *s2);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
int				ft_strcmp(char *s1, char *s2);
void			ft_strcpy(char *dst, const char *src);
void			ft_strncpy(char *dest, const char *src, size_t len);
size_t			ft_strlcpy(char *dest, const char *src, size_t destsize);
char			*ft_itoa(int n);
int				ft_atoi(const char *str);

t_stack			*stack_init(void);
t_stack_node	*ft_new_stack_node(char quote);
void			ft_push(t_stack *stack, char quote);
t_stack_node	*ft_pop(t_stack *stack);
void			ft_free_stack(t_stack *stack);

#endif
