#include "utils.h"

//Not Implemeted yet
t_tree	*get_tree(char *line)
{
	t_tree	*tree;
	t_list	*list;

	// lexer			: return list of lexical_tokens
	// syntax checker	: return 0 if syntax has no error else -1
	// tree builder		: return pointer of tree
	//					: each level call their lower process functs recursively

	//list = get_lexica(line);
	tree = tree_builder(list);
	if (!tree)
		free_tree(tree);
	return (tree);
}
