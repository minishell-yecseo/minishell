#ifndef UTILS_H
# define UTILS_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "ft_strings.h"
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

extern int	g_last_exit_code;

t_tree		*get_tree(char *line, char **envp);

//level 01
//			: Replace all $envp values
char		*get_line_replace_envp(char *line, char **envp);
char		*get_replaced_line(char *line, char *dolor, int *len, char **envp);
int			get_key_len(char *dolor);
char		*get_line_with_value(char *line, char *dolor, \
								char *key, char *value);
char		*get_value(char *key, char **envp);
char		*get_key_from_envp(char *envp);
char		*get_value_with_flag(char *envp, int envp_key_len, int find, char *key);

//level 02
//			: Split tokens and build lists
t_list		*lexer(char *line, char **envp);
void		set_list_from_line(t_list **head, char *line);
int			add_redir(t_list **head, char *line);
int			add_quotes(t_list **head, char *line);
int			add_pipe(t_list **head, char *line);
int			add_word(t_list **head, char *line);

//level 03
//			: check syntax
int			syntax(t_list **head);//utils.c
void		line_syn_err(void);//utils.c

//level 04
//			: Build tree with tokenized lists
t_tree		*tree_builder(t_list *head);
void		set_pipe(t_node *parent, t_list *start, t_list *last);
void		set_cmd(t_node *parent, t_list *start, t_list *last);
void		set_redir(t_node *parent, t_list *start, t_list *last);
void		set_simple_cmd(t_node *parent, t_list *start, t_list *last);
char		*get_path(t_list *start, char **envps);
char		**get_args(t_list *start, t_list *last);
int			get_list_range_size(t_list *start, t_list *last);
int			get_redir_num_in_range(t_list *start, t_list *last);
t_list		*get_word_start_list(t_list *start, t_list *last, int redir_num);
t_list		*get_word_end_list(t_list *start, t_list *last);

//free utils
void		free_line_list(t_list *head);//utils.c

//list utils
t_list		*ft_lstnew(t_l_type type, char *line);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);

#endif
