/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saseo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 19:21:18 by saseo             #+#    #+#             */
/*   Updated: 2023/04/17 19:21:19 by saseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"
#include "minishell.h"

void	set_last_exit_code(t_tree *tree, int err, int status)
{
	err = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		g_last_exit_code = 128 + WTERMSIG(status);
		write(1, "\n", 1);
	}
	else if (tree->is_last_exit == 1)
		g_last_exit_code = err;
	else
	{
		if (err == 2)
			g_last_exit_code = 127;
		else if (err == 13)
			g_last_exit_code = 126;
		else
			g_last_exit_code = err;
	}
}

void	wait_forks(t_tree *tree)
{
	int		err;
	int		status;
	pid_t	pid;

	pid = 0;
	err = 0;
	while (pid != -1)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == tree->pid)
		{
			set_last_exit_code(tree, err, status);
		}
	}
}
