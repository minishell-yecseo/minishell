#include "minishell.h"
#include "tree.h"

void forked_exe(t_tree *tree, t_node *cur, char ***envp)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &tree->term);
	restore_sig();
	close(tree->stdfds[0]);
	close(tree->stdfds[1]);
	close(tree->fds[0]);
	if (tree->filefds[1] <= 0)
		dup2(tree->fds[1], 1);
	close(tree->fds[1]);
	if (check_char(cur->cont.args[0], '/'))
		path_exe(cur->cont.args, envp);
	else if (check_built_in(cur->cont.args[0], cur->cont.args, envp))
		;
	else if (!check_path(*envp))
	{
		execve(cur->cont.args[0], cur->cont.args, *envp);
	}
	else if (check_exefile(cur, *envp))
	{
		execve(cur->cont.path, cur->cont.args, *envp);
	}
	else
	{
		ft_print_err(cur->cont.args[0]);
		write(2, "command not found\n", 18);
		exit(1);
	}
	perror(cur->cont.args[0]);
	exit(errno);
}

void	exe_simple_com(t_tree *tree, t_node *cur, char ***envp)
{
	pid_t pid;
	
	if (tree->err == 0)
	{
		pid = fork();
		if (pid == 0)
			forked_exe(tree, cur, envp);
		else if (pid > 0)
		{
			close(tree->fds[1]);
			dup2(tree->fds[0], 0);
			close(tree->fds[0]);
		}
		else
		{
			perror("fork");
			exit(1);
		}
	}
	else
	{
		close(tree->fds[1]);
		close(tree->fds[0]);
		tree->err = 0;
	}
}

void last_forked_exe(t_tree *tree, t_node *cur, char ***envp)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &tree->term);
	restore_sig();
	if (tree->filefds[1] <= 0)
		dup2(tree->stdfds[1], 1);
	close(tree->stdfds[1]);
	if (check_char(cur->cont.args[0], '/'))
		path_exe(cur->cont.args, envp);
	else if (check_built_in(cur->cont.args[0], cur->cont.args, envp))
		;
	else if (!check_path(*envp))
	{
		execve(cur->cont.args[0], cur->cont.args, *envp);
		perror(cur->cont.args[0]);
		exit(2);
	}
	else if (check_exefile(cur, *envp))
	{
		execve(cur->cont.path, cur->cont.args, *envp);
	}
	else
	{
		ft_print_err(cur->cont.args[0]);
		ft_print_err(": command not found\n");
		exit(2);
	}
	perror(cur->cont.args[0]);
	exit(1);
}

void	last_simple_com(t_tree *tree, t_node *cur, char ***envp)
{
	pid_t	pid;

	if (tree->err == 0)
	{
		if (tree->first == 0 && only_check_built_in(cur->cont.args[0]))
			g_last_exit_code = one_exe_built_in(cur->cont.args[0], cur->cont.args, envp);
		else
		{
			pid = fork();
			if (pid == 0)
				last_forked_exe(tree, cur, envp);
			else if (pid > 0)
			{
				if (!ft_strcmp(cur->cont.args[0], "exit"))
					tree->is_last_exit = 1;
				tree->pid = pid;
				dup2(tree->stdfds[0], 0);
			}
			else
			{
				perror("fork");
				exit(3);
			}
		}
	}
	else
		g_last_exit_code = 1;
}
