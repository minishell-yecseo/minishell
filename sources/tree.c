#include "minishell.h"

t_tree	*init_tree(void)
{
	t_tree	*tree;

	tree = (t_tree *)ft_calloc(1, sizeof(t_tree));
	if (!tree)
		exit(0);
	tree->root = NULL;
	tree->size = 0;
	return (tree);
}

t_node	*create_node(t_token type)
{
	t_node	*node;

	node = (t_node *)ft_calloc(1, sizeof(t_node));
	if (!node)
		exit(0);
	node->type = type;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

void	tree_set_root(t_tree *tree, t_node *root)
{
	if (!tree)
		return ;
	tree->root = root;
}

void	insert_left(t_node *parent, t_node *child)
{
	parent->left = child;
}

void	insert_right(t_node *parent, t_node *child)
{
	parent->right = child;
}

int	traverse(t_tree *tree, t_node *cur, char ***envp)
{
	if (!tree)
		return (0);
	if (!cur)
		return (0);
	if (DEBUG)
	{
		print_token_type(cur);
		print_cont(&(cur->cont), cur->type);
	}
	exe_cur(tree, cur, envp);
	traverse(tree, cur->left, envp);
	traverse(tree, cur->right, envp);
	return (0);
}

void	free_tree(t_tree *tree)
{
	t_node	*node;
	t_node	*tmp;

	if (!tree)
		return ;
	node = tree->root;
	if (tree->root == NULL)
	{
		free(tree);
		return ;
	}
	free_tree_node(node);
	free(tree);
}

void	free_tree_node(t_node *node)
{
	if (node == NULL)
		return ;
	free_tree_node(node->left);
	free_tree_node(node->right);
	free_node_type(node);
	free(node);
}

void	free_node_type(t_node *node)
{
	if (node->type == REDIR)
		free(node->cont.file_name);
	else if (node->type == SIMPLE_CMD)
		free_node_simple_cmd(node);
	node = NULL;
}

void	free_node_simple_cmd(t_node *node)
{
	char	**tmp;

	tmp = node->cont.args;
	free(node->cont.path);
	while (*tmp)
	{
		free(*tmp);
		tmp++;
	}
	free(node->cont.args);
}
