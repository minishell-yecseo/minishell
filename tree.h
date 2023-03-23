#ifndef TREE_H
# define TREE_H

# include "token.h"
# include <stdlib.h>
# include <stdio.h>

typedef struct s_node
{
	enum e_token	type;//can be PIPE, CMD, REDIR, SIMPLE_CMD
	union u_cont	cont;//can be a pointer of struct s_pipe, s_cmd, s_redir, s_simple_cmd
	struct s_node	*left;
	struct s_node	*right;
}					t_node;

typedef struct s_tree
{
	struct s_node	*head;
	int				size;
}					t_tree;

t_tree	*init_tree(void);
t_node	*create_node(t_token type);
void	insert_left(t_tree *tree, t_node *parent, t_node *child);
void	insert_right(t_tree *tree, t_node *parent, t_node *child);

int		traverse(t_tree *tree, t_node *cur);

void	print_token_type(t_node *node);
void	print_cont(t_cont *cont, t_token type);

#endif
