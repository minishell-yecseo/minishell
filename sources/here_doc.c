#include "minishell.h"
#include "tree.h"

void	exe_heredoc(t_tree *tree, t_node *cur, char ***envp)
{
	char	*itoa;
	char	*path;

	itoa = ft_itoa(tree->here_num);
	path = ft_strjoin("/tmp/minishell.here_doc.", itoa);
	if (!itoa || !path)
		func_err("heredoc: malloc");
	tree->filefds[0] = open(path, O_RDONLY);
	free(path);
	free(itoa);
	if (tree->filefds[0] == -1)
	{
		tree->err = 1;
		perror(cur->cont.file_name);
		return ;
	}
	ft_dup2(tree->filefds[0], 0);
	ft_close(tree->filefds[0]);
	tree->here_num += 1;
}

void	get_here_line(t_tree *tree, t_node *cur, char ***envp)
{
	char	*input;
	char	*tmp;

	while (1)
	{
		input = readline("> ");
		if (!input)
			break ;
		if (!ft_strcmp(input, cur->cont.file_name))
			break ;
		tmp = input;
		input = here_doc_replace_envp(input, *envp);
		free(tmp);
		write(tree->filefds[1], input, ft_strlen(input));
		write(tree->filefds[1], "\n", 1);
		free(input);
	}
	if (input)
		free(input);
}

void	here_doc_fork(t_tree *tree, t_node *cur, char ***envp)
{	
	struct sigaction	sig;
	char				*input;
	char				*num;
	char				*path;

	sig.sa_handler = SIG_DFL;
	sigaction(SIGINT, &sig, 0);
	num = ft_itoa(tree->here_num);
	path = ft_strjoin("/tmp/minishell.here_doc.", num);
	if (!num || !path)
		func_err("heredoc: malloc");
	free(num);
	tree->filefds[1] = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	get_here_line(tree, cur, envp);
	free(path);
	ft_close(tree->filefds[1]);
	//system("leaks minishell");
	exit(0);
}

void	here_doc_wait(t_tree *tree, pid_t pid)
{
	int		status;

	tree->here_num += 1;
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		tree->here_doc = 1;
		g_last_exit_code = 1;
	}
}

int	here_traverse(t_tree *tree, t_node *cur, char ***envp)
{
	pid_t	pid;

	if (!tree)
		return (0);
	if (!cur)
		return (0);
	if (cur->type == REDIR && cur->cont.redir_type == HERE_DOC)
	{
		if (tree->here_doc != 1)
		{
			pid = fork();
			if (pid == 0)
				here_doc_fork(tree, cur, envp);
			else if (pid > 0)
				here_doc_wait(tree, pid);
			else
				func_err("fork");
		}
	}
	here_traverse(tree, cur->left, envp);
	here_traverse(tree, cur->right, envp);
	return (0);
}
