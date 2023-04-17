#include "minishell.h"

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
