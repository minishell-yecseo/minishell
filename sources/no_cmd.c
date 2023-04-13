#include "minishell.h"

void	no_cmd(t_tree *tree, t_node *cur, char ***envp)
{
	if (tree->last != 1)
	{
		if (close(tree->fds[1] == -1))
			func_err("close");
		if (close(tree->fds[0]) == -1)
			func_err("close");
	}
	if (dup2(tree->stdfds[0], 0) == -1)
		func_err("dup2");
	if (dup2(tree->stdfds[1], 1) == -1)
		func_err("dup2");
}
