#include "minishell.h"

void	no_cmd(t_tree *tree, t_node *cur, char ***envp)
{
	if (tree->last != 1)
	{
		close(tree->fds[1]);
		close(tree->fds[0]);
	}
	dup2(tree->stdfds[0], 0);
	dup2(tree->stdfds[1], 1);
}