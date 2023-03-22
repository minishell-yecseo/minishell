#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include "tree.h"

int	main(int argc, char **argv, char **envp)
{
	t_tree	*tree;

	// 일단은 단순하게 테스트용으로 다시 넣어봤습니다.
	tree = init_tree();
	tree->head = create_node("|", PIPE);
	insert_left(tree, tree->head, create_node("<test.txt cat", CMD));
	insert_right(tree, tree->head, create_node("grep hello", PIPE));
	insert_right(tree, tree->head->right, create_node("grep hello", SIMPLE_CMD));
	insert_left(tree, tree->head->left, create_node("<test.txt", REDIRECT));
	insert_right(tree, tree->head->left, create_node("cat", SIMPLE_CMD));
	traverse(tree->head, tree->head);
	return 0;
}
