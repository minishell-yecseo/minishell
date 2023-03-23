#include "tree.h"

void	exe_pipe(t_tree *tree, t_node *cur)
{
	if (cur->right != 0)
		pipe(tree->fds);
	else
		tree->last = 1;
}

void	exe_redir(t_tree *tree, t_node *cur)
{
	if (tree->err == 1)
			return ;
	if (cur->cont.redir_type == IN)
	{
		tree->filefds[0] = open(cur->cont.file_name, O_RDONLY);
		if (tree->filefds[1] == -1)
		{
			tree->err = 1;
			perror(cur->cont.file_name);
		}
		dup2(tree->filefds[0], 0);
		close(tree->filefds[0]);
	}
	else if (cur->cont.redir_type == HERE_DOC)
	{
		if (tree->err == 1)
			return ;
	}
	else if (cur->cont.redir_type == OUT_T)
	{
		if (tree->err == 1)
			return ;
		tree->filefds[1] = open(cur->cont.file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (tree->filefds[1] == -1)
		{
			tree->err = 1;
			perror(cur->cont.file_name);
		}
		dup2(tree->filefds[1], 1);
		close(tree->filefds[1]);
	}
	else if (cur->cont.redir_type == OUT_A)
	{
		if (tree->err == 1)
			return ;
		tree->filefds[1] = open(cur->cont.file_name, O_RDWR | O_CREAT | O_APPEND, 0644);
		if (tree->filefds[1] == -1)
		{
			tree->err = 1;
			perror(cur->cont.file_name);
		}
		dup2(tree->filefds[1], 1);
		close(tree->filefds[1]);
	}
}

void	exe_simple_com(t_tree *tree, t_node *cur)
{
	int pid;
	
	if (tree->last == 1)
	{
		pid = fork();
		if (pid == 0)
		{
			execve(cur->cont.path, cur->cont.args, 0);
			//perror(cur->cont.path);
			return ;
		}
		else
		{
			return ;
		}
	}
	pid = fork();
	if (pid == 0)
	{
		close(tree->fds[0]);
		//if (tree->filefds[0] > 0)	
		if (tree->filefds[1] > 0)
			;
		else
			dup2(tree->fds[1], 1);
		if (tree->err != 1)
		{
			execve(cur->cont.path, cur->cont.args, 0);
			perror("");
		}
		else
			exit (1);
	}
	else
	{
		close(tree->fds[1]);
		dup2(tree->fds[0], 0);
		close(tree->fds[0]);
	}
}

void	exe_cur(t_tree *tree, t_node *cur)
{
	if (cur->type == PIPE)
		exe_pipe(tree, cur);
	else if (cur->type == CMD)
		;
	else if (cur->type == REDIR)
		exe_redir(tree, cur);
	else if (cur->type == SIMPLE_CMD)
		exe_simple_com(tree, cur);
}
