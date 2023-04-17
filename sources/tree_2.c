#include "tree.h"

void	tree_set_root(t_tree *tree, t_node *root)
{
	if (!tree)
		return ;
	tree->root = root;
}

void	free_tree(t_tree *tree)
{
	t_node	*node;

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
