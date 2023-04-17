#include "minishell.h"

void	no_cmd(t_tree *tree)
{
	if (tree->last != 1)
	{
		ft_close(tree->fds[1]);
		ft_close(tree->fds[0]);
	}
	ft_dup2(tree->stdfds[0], 0);
	ft_dup2(tree->stdfds[1], 1);
}
