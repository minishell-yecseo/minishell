/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:30:40 by yecnam            #+#    #+#             */
/*   Updated: 2023/04/17 16:32:44 by yecnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <dirent.h>
# include "libft.h"
# include "tree.h"

typedef enum e_char_type
{
	ZERO,
	WHITE_SPACE,
	QUOTE,
	C_REDIR,
	C_PIPE,
	OTHER
}	t_char_type;

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
	int					is_end;
	int					is_quote;
	struct s_list		*prev;
	struct s_list		*next;
}			t_list;

extern int	g_last_exit_code;

t_tree		*get_tree(char *line, char **envp);

char		*get_line_replace_envp(char *line, char **envp);
char		*get_replaced_line(char *line, char *dolor, int *len, char **envp);
int			get_key_len(char *dolor);
char		*get_line_with_value(char *line, char *dolor, \
								char *key, char *value);
char		*get_value(char *key, char **envp);
char		*get_key_from_envp(char *envp);
char		*get_value_with_flag(char *envp, char *e_key, int find, char *key);
char		*free_and_replace_line(char *old, char *line, int *len, char **en);
void		set_quote_flag(char *line, char *flag);
void		set_heredoc_flag(char *line, char *flag);

t_list		*lexer(char *line, char **envp);
void		set_list_from_line(t_list **head, char *line);
int			add_redir(t_list **head, char *line);
int			add_quotes(t_list **head, char *line);
int			add_pipe(t_list **head, char *line);
int			add_word(t_list **head, char *line);
int			char_type_for_list(char c);
void		build_list_with_space(t_list *head);
void		tokens_to_one(t_list *list);
void		free_sub_list(t_list *start, t_list *last);

int			get_quotes_len_for_list(char *line);
void		set_quotes_list_end_var(t_list *quote_list, char *line, int len);
int			get_word_len_for_list(char *line);
void		set_word_list_end_var(t_list *word_list, char *line, int len);

int			build_list_with_asterisk(t_list **head);
void		set_here_doc_flag(t_list *node, int *is_next_to_heredoc);
t_list		*get_entry_name_list(int *status);
void		dup_and_add_list_entry_name(t_list **head, char *name);
void		join_aster_list(t_list **head, t_list *node, t_list *aster_list);
int			dir_open_err(void);

int			pre_syntax_checker(char *line);
int			quote_pair_syntax_checker(char *line);
int			post_syntax_checker(t_list *head);
int			redir_syntax_checker(t_list *head);
int			pipe_syntax_checker(t_list *head);
int			parenthesis_pair_checker(char *line);
int			parenthesis_with_stack(t_stack *stack, char *line);

void		line_syn_err(char *line);
void		quote_err(void);

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

t_list		*ft_lstnew(t_l_type type, char *line);
t_list		*ft_lstlast(t_list *lst);
int			ft_lstadd_back(t_list **lst, t_list *new);
void		sort_list_by_line(t_list **head);
int			get_list_len(t_list *node);
void		list_swap_with_next(t_list **head, t_list *node);

void		ft_print_list(t_list *lst);
void		print_list_type(t_list *lst);
void		free_line_list(t_list *head);

char		*here_doc_replace_envp(char *line, char **envp);

void		ft_print_err(char *str);
void		func_err(char *str);
void		malloc_fail(void);

#endif
