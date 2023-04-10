#include "minishell.h"
#include "tree.h"

void	exe_pipe(t_tree *tree, t_node *cur)
{
	tree->filefds[0] = 0;
	tree->filefds[1] = 0;
	tree->err = 0;
	///STDIN, STDTOUT restore
	//dup2(tree->stdfds[0], 0);
	//dup2(tree->stdfds[1], 1);
	//close(tree->stdfds[0]);
	//close(tree->stdfds[1]);
	//tree->stdfds[0] = dup(0);
	//tree->stdfds[1] = dup(1);
	if (cur->left == 0)
		return ;
	if (cur->right->left != 0)
	{
		pipe(tree->fds);
		tree->first += 1;
	}
	else
	{
		tree->last = 1;
	}
}

void	exe_redir(t_tree *tree, t_node *cur, char ***envp)
{
	if (tree->err != 0)
			return ;
	if (cur->cont.redir_type == IN)
	{
		tree->filefds[0] = open(cur->cont.file_name, O_RDONLY);
		//printf("%d\n\n", tree->filefds[0]);
		if (tree->filefds[0] == -1)
		{
			tree->err = 1;
			perror(cur->cont.file_name);
		}
		dup2(tree->filefds[0], 0);
		close(tree->filefds[0]);
	}
	else if (cur->cont.redir_type == HERE_DOC)
	{
		char *itoa = ft_itoa(tree->here_num);
		char *path = ft_strjoin("/tmp/minishell.here_doc.", itoa);
		tree->filefds[0] = open(path, O_RDONLY);
		free(path);
		free(itoa);
		if (tree->filefds[0] == -1)
		{
			tree->err = 1;
			perror(cur->cont.file_name);
		}
		dup2(tree->filefds[0], 0);
		close(tree->filefds[0]);
		tree->here_num += 1;
	}
	else if (cur->cont.redir_type == OUT_T)
	{
		tree->filefds[1] = open(cur->cont.file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (tree->filefds[1] == -1)
		{
			tree->err = 1;
			perror(cur->cont.file_name);
			return ;
		}
		dup2(tree->filefds[1], 1);
		close(tree->filefds[1]);
	}
	else if (cur->cont.redir_type == OUT_A)
	{
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

void	exe_cur(t_tree *tree, t_node *cur, char ***envp)
{
	if (cur->type == PIPE)
		exe_pipe(tree, cur);
	else if (cur->type == CMD)
		;
	else if (cur->type == REDIR)
		exe_redir(tree, cur, envp);
	else if (cur->type == SIMPLE_CMD && tree->last == 0)
	{
		exe_simple_com(tree, cur, envp);
	}
	else if (cur->type == SIMPLE_CMD && tree->last == 1)
	{
		last_simple_com(tree, cur, envp);
	}	
	else if (cur->type == NO_CMD)
	{
		no_cmd(tree, cur, envp);
	}
}
