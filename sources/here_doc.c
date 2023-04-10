#include "minishell.h"
#include "tree.h"

void	here_del(void)
{
	int		i;
	char	*path;

	i = 0;
	while (1)
	{
		path = ft_strjoin("/tmp/minishell.here_doc.", ft_itoa(i));
		if (!path)
			malloc_fail();
		if (unlink(path) != 0)
			break ;
		i++;
		free(path);
	}
	free(path);
}

void	here_traverse(t_tree *tree, t_node *cur, char ***envp)
{
	pid_t	pid;

	if (!tree)
		return ;
	if (!cur)
		return ;
	if (cur->type == REDIR)
	{
		if (cur->cont.redir_type == HERE_DOC)
		{
			pid = fork();
			if (pid == 0)
			{
				char *input;
				char *path = ft_strjoin("/tmp/minishell.here_doc.", ft_itoa(tree->here_num));
				tree->filefds[1] = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				while (1)
				{
					input = readline("> ");
					if (!ft_strcmp(input, cur->cont.file_name))
						break ;
					input = here_doc_replace_envp(input, *envp);
					write(tree->filefds[1], input, ft_strlen(input));
					write(tree->filefds[1], "\n", 1);
					free(input);
				}
				free(path);
				free(input);
				close(tree->filefds[1]);
				exit(0);
			}
			else if (pid > 0)
			{
				waitpid(pid, 0, 0);
				tree->here_num += 1;
			}
			else
			{
				perror("fork");
				exit(1);
			}
		}
	}
	
	here_traverse(tree, cur->left, envp);
	here_traverse(tree, cur->right, envp);
	return ;
}