#include "utils.h"

t_tree	*get_tree(char *line, char **envp)
{
	t_tree	*tree;
	t_list	*list;
	int		syntax_flag;

	syntax_flag = 1;
	list = lexer(line, envp);
	if (!list)
		return (NULL);
	syntax_flag = post_syntax_checker(list);
	if (!syntax_flag)
	{
		free_line_list(list);
		return (NULL);
	}
	tree = tree_builder(list);
	free_line_list(list);
	return (tree);
}
