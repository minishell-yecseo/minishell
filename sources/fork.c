#include "tree.h"
#include "minishell.h"
//#define WEXITSTATUS(x)  ((_W_INT(x) >> 8) & 0x000000ff)

extern int	g_last_exit_code;

void	wait_forks(t_tree *tree)
{
	int err;
	int status;
	int pid;

	pid = 0;
	while (pid != -1)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == tree->pid)
		{
			err = WEXITSTATUS(status);
			if (WIFSIGNALED(status))
			{
				printf("hi");
				g_last_exit_code = 128 + WTERMSIG(status);
			}
			else if (tree->is_last_exit == 1)
			{
				g_last_exit_code = err;
			}
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
	}
}