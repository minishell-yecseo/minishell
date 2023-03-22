#include "tree.h"

t_tree	*init_tree(void)
{
	t_tree	*tree;

	tree = (t_tree *) malloc(sizeof(t_tree));
	if (!tree)
		exit(0);
	tree->head = NULL;
	tree->size = 0;
	return (tree);
}

t_node	*create_node(void *value, t_token type)
{
	t_node	*node;

	node = (t_node *) malloc(sizeof(t_node));
	if (!node)
		exit(0);
	node->type = type;
	node->value = value;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

void	insert_left(t_tree *tree, t_node *parent, t_node *child)
{
	if (!tree || !(tree->head))
		return ;
	parent->left = child;
	tree->size += 1;
}

void	insert_right(t_tree *tree, t_node *parent, t_node *child)
{
	if (!tree || !(tree->head))
		return ;
	parent->right = child;
	tree->size += 1;
}

void	print_token_type(t_node *node)
{
	if (node->type == PIPE)
		printf("PIPE");
	else if (node->type == CMD)
		printf("CMD");
	else if (node->type == REDIRECT)
		printf("REDIRECT");
	else if (node->type == SIMPLE_CMD)
		printf("SIMPLE_CMD");
}

int	traverse(t_node *root, t_node *cur)
{
	if (!cur)
		return (0);
	print_token_type(cur);
	printf(":: %s\n", (char *) cur->value);
	traverse(root, cur->left);
	traverse(root, cur->right);
	return (0);
}
