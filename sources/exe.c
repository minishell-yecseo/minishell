#include "minishell.h"
#include "tree.h"

void	exe_pipe(t_tree *tree, t_node *cur)
{
	tree->filefds[0] = 0;
	tree->filefds[1] = 0;
	tree->err = 0;
	if (cur->left == 0)
		return ;
	if (cur->right->left != 0)
	{
		if (pipe(tree->fds) == -1)
			func_err("pipe");
		tree->first += 1;
	}
	else
		tree->last = 1;
}

void	exe_in(t_tree *tree, t_node *cur, char ***envp)
{
	tree->filefds[0] = open(cur->cont.file_name, O_RDONLY);
	if (tree->filefds[0] == -1)
	{
		tree->err = 1;
		perror(cur->cont.file_name);
		return ;
	}
	if (dup2(tree->filefds[0], 0) == -1)
		func_err("dup2");
	if (close(tree->filefds[0]) == -1)
		func_err("close");
}

void	exe_out_t(t_tree *tree, t_node *cur, char ***envp)
{
	tree->filefds[1] = open(cur->cont.file_name, \
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (tree->filefds[1] == -1)
	{
		tree->err = 1;
		perror(cur->cont.file_name);
		return ;
	}
	if (dup2(tree->filefds[1], 1) == -1)
		func_err("dup2");
	if (close(tree->filefds[1]) == -1)
		func_err("close");
}

void	exe_redir(t_tree *tree, t_node *cur, char ***envp)
{
	if (tree->err != 0)
		return ;
	if (cur->cont.redir_type == IN)
		exe_in(tree, cur, envp);
	else if (cur->cont.redir_type == HERE_DOC)
		exe_heredoc(tree, cur, envp);
	else if (cur->cont.redir_type == OUT_T)
		exe_out_t(tree, cur, envp);
	else if (cur->cont.redir_type == OUT_A)
	{
		tree->filefds[1] = open(cur->cont.file_name, \
					O_RDWR | O_CREAT | O_APPEND, 0644);
		if (tree->filefds[1] == -1)
		{
			tree->err = 1;
			perror(cur->cont.file_name);
		}
		if (dup2(tree->filefds[1], 1) == -1)
			func_err("dup2");
		if (close(tree->filefds[1]) == -1)
			func_err("close");
	}
}

void	exe_cur(t_tree *tree, t_node *cur, char ***envp)
{
	if (cur->type == PIPE)
		exe_pipe(tree, cur);
	else if (cur->type == CMD)
		return ;
	else if (cur->type == REDIR)
		exe_redir(tree, cur, envp);
	else if (cur->type == SIMPLE_CMD && tree->last == 0)
		exe_simple_com(tree, cur, envp);
	else if (cur->type == SIMPLE_CMD && tree->last == 1)
		last_simple_com(tree, cur, envp);
	else if (cur->type == NO_CMD)
		no_cmd(tree, cur, envp);
}
