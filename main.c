#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include "tree.h"

int	main(int argc, char **argv, char **envp)
{
	t_tree	*tree;

	tree = init_tree();
	tree->head = create_node("head");
	insert_left(tree, tree->head, create_node("left"));
	insert_right(tree, tree->head, create_node("right"));
	traverse(tree->head, tree->head);
	return 0;
}
