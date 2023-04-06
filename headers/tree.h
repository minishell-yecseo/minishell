#ifndef TREE_H
# define TREE_H

# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <errno.h>
# include <termios.h>

typedef enum e_token
{
	PIPE,
	CMD,
	REDIR,
	SIMPLE_CMD,
	NO_CMD
}			t_token;

typedef enum e_redir_type
{
	IN,
	HERE_DOC,
	OUT_T,
	OUT_A
}			t_redir_type;

typedef struct s_cont
{
	int				is_pipe;
	int				fds[2];
	int				filefds[2];
	t_redir_type	redir_type;
	char			*file_name;
	int				fd;
	char			*path;
	char			**args;
}			t_cont;

typedef struct s_node
{
	enum e_token	type;
	struct s_cont	cont;
	struct s_node	*left;
	struct s_node	*right;
}					t_node;

typedef struct s_tree
{
	struct s_node	*root;
	int				size;
	int				last;
	int				err;
	pid_t			pid;
	int				first;
	int				fds[2];
	int				stdfds[2];
	int				filefds[2];
	struct			termios term;
}					t_tree;

t_tree	*init_tree(void);
void	tree_set_root(t_tree *tree, t_node *node);
t_node	*create_node(t_token type);
void	insert_left(t_node *parent, t_node *child);
void	insert_right(t_node *parent, t_node *child);

int		traverse(t_tree *tree, t_node *cur, char ***envp);

void	free_tree(t_tree *tree);
void	free_tree_node(t_node *node);
void	free_node_type(t_node *node);
void	free_node_simple_cmd(t_node *node);

void	print_token_type(t_node *node);
void	print_cont(t_cont *cont, t_token type);

#endif
