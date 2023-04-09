#include "utils.h"

t_tree	*get_tree(char *line, char **envp)
{
	t_tree	*tree;
	t_list	*list;

	list = lexer(line, envp);
	if (!list)
		return (NULL);
	tree = tree_builder(list);
	free_line_list(list);
	return (tree);
}
