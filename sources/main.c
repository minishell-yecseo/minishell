#include "minishell.h"

static void	set_test_list(t_list **head);

void	unset_oldpath(char ***envp)
{
	*envp = oldpwd_envp(envp, "OLDPWD");
}

char	**cp_envp(char **envp)
{
	int		i;
	char	**en;

	i = 0;
	while (envp[i])
		i++;
	en = (char **)malloc(sizeof(char *) * (i + 1));
	if (!en)
		exit(1);
	i = 0;
	while (envp[i])
	{
		en[i] = ft_strdup(envp[i]);
		if (!en[i])
			exit(1);
		i++;
	}
	en[i] = 0;
	return (en);
}

int	main(int argc, char **argv, char **en)
{
	char				**envp;
	t_tree				*tree;
	char				*line;
	struct sigaction	sig;
	struct termios		old_term;
	struct termios		term;

	minishell_sig_setting(&sig, &old_term, &term);
	envp = cp_envp(en);
	unset_oldpath(&envp);
	print_init_msg();
	while (1)
	{
		line = readline("\x1b[38;5;204mminishell-0.1$\x1b[0m ");
		if (!line)
			program_end(old_term);
		else if (*line)
		{
			tree = get_tree(line, envp);
			add_history(line);
			if (!tree)
			{
				free(line);
				continue ;
			}
			tree->stdfds[0] = dup(0);
			tree->stdfds[1] = dup(1);
			tree->sig = sig;
			tree->term = old_term;
			tree->new = term;
			ignore_sig();
			here_traverse(tree, tree->root, &envp);
			if (!tree->here_doc)
			{
				tree->here_num = 0;
				tcsetattr(STDIN_FILENO, TCSANOW, &old_term);
				traverse(tree, tree->root, &envp);
				wait_forks(tree);
				tcsetattr(STDIN_FILENO, TCSANOW, &term);
			}
			dup2(tree->stdfds[1], 1);
			dup2(tree->stdfds[0], 0);
			close(tree->stdfds[0]);
			close(tree->stdfds[1]);
			free_tree(tree);
			here_del();
			change_sig(tree);
		}
		free(line);
	}
	return (0);
}
