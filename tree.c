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

t_node	*create_node(void *value)
{
	t_node	*node;

	node = (t_node *) malloc(sizeof(t_node));
	if (!node)
		exit(0);
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

int	traverse(t_node *root, t_node *cur)
{
	if (!cur)
		return (0);
	// 현재 노드에 대해서 어떤 동작을 할지는 실행부의 역할
	// 일단 value에 string이 들어온다는 가정을 하고
	// printf로 value를 출력하겠습니다.
	printf("%s\n", (char *) cur->value);
	traverse(root, cur->left);
	traverse(root, cur->right);
	return (0);
}
