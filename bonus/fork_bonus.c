/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:31:24 by yecnam            #+#    #+#             */
/*   Updated: 2023/04/17 16:33:14 by yecnam           ###   ########.fr       */
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
