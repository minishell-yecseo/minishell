#ifndef TREE_H
# define TREE_H
#endif

#include <stdlib.h>
#include <stdio.h>

typedef struct	s_node {
	void			*value;
	struct s_node	*left;
	struct s_node	*right;
}				t_node;

typedef struct	s_tree {
	struct s_node	*head;
	int				size;
}				t_tree;

t_tree	*init_tree(void);
t_node	*create_node(void *value);
void	insert_left(t_tree *tree, t_node *parent, t_node *child);
void	insert_right(t_tree *tree, t_node *parent, t_node *child);

int		traverse(t_node *root, t_node *cur);
