/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_setting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saseo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:31:58 by saseo             #+#    #+#             */
/*   Updated: 2023/04/17 16:31:59 by saseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tree_set_exe(t_tree *tree, t_set sa)
{
	tree->stdfds[0] = dup(0);
	tree->stdfds[1] = dup(1);
	if (tree->stdfds[0] == -1 || tree->stdfds[1] == -1)
		func_err("dup");
	tree->sig = sa.sig;
	tree->term = sa.old_term;
	tree->new = sa.term;
}

void	tree_start(t_tree *tree, char *line, char ***envp, t_set sa)
{
	tree = get_tree(line, *envp);
	add_history(line);
	free(line);
	if (!tree)
		return ;
	tree_set_exe(tree, sa);
	ignore_sig();
	here_traverse(tree, tree->root, envp);
	if (!tree->here_doc)
	{
		tree->here_num = 0;
		tcsetattr(STDIN_FILENO, TCSANOW, &sa.old_term);
		traverse(tree, tree->root, envp);
		ft_dup2(tree->stdfds[1], 1);
		ft_dup2(tree->stdfds[0], 0);
		ft_close(tree->stdfds[0]);
		ft_close(tree->stdfds[1]);
		wait_forks(tree);
		tcsetattr(STDIN_FILENO, TCSANOW, &sa.term);
	}
	free_tree(tree);
	here_del();
}
