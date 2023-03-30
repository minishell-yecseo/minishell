#ifndef UTILS_H
# define UTILS_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "tree.h"

typedef enum e_l_type
{
	L_PIPE,
	L_REDIR,
	L_WORD
}			t_l_type;

typedef struct s_list
{
	enum e_l_type		type;
	char				*line;
	struct s_list		*prev;
	struct s_list		*next;
}			t_list;

t_tree		*get_tree(char *line);

t_list		*lexer(char *line);
char		*replace_envp(char *line);

int			syntax(t_list *head);

t_tree		*tree_bulider(t_list *head);
void		set_pipe(t_node *parent, t_list *start, t_list *last);
void		set_cmd(t_node *parent, t_list *start, t_list *last);
void		set_redir(t_node *parent, t_list *start, t_list *last);
void		set_simple_cmd(t_node *parent, t_list *start, t_list *last);
char		*get_path(t_list *start, char **envps);
char		**get_args(t_list *start, t_list *last);

int			add_redir(t_list **list, char *line, char **envp);
int			add_quotes(t_list **list, char *line, char **envp);
int			add_pipe(t_list **list, char *line, char **envp);
int			add_word(t_list **list, char *line, char **envp);

char		*get_end_addr(char *str, char *delimiters);

char		**dup_envp(char **envp);
void		free_all(char **strs, int len);

t_list		*ft_lstnew(t_l_type type, char *line);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);

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
