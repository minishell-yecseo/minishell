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
		func_err("malloc");
	i = 0;
	while (envp[i])
	{
		en[i] = ft_strdup(envp[i]);
		if (!en[i])
			func_err("strdup");
		i++;
	}
	en[i] = 0;
	return (en);
}

void	tree_set_exe(t_tree *tree, t_set sa)
{
	tree->stdfds[0] = dup(0);
	tree->stdfds[1] = dup(1);
	tree->sig = sa.sig;
	tree->term = sa.old_term;
	tree->new = sa.term;
}

void	tree_start(t_tree *tree, char *line, char **envp, t_set sa)
{
	tree = get_tree(line, envp);
	add_history(line);
	free(line);
	if (!tree)
		return ;
	tree_set_exe(tree, sa);
	ignore_sig();
	here_traverse(tree, tree->root, &envp);
	if (!tree->here_doc)
	{
		tree->here_num = 0;
		tcsetattr(STDIN_FILENO, TCSANOW, &sa.old_term);
		traverse(tree, tree->root, &envp);
		dup2(tree->stdfds[1], 1);
		dup2(tree->stdfds[0], 0);
		close(tree->stdfds[0]);
		close(tree->stdfds[1]);
		wait_forks(tree);
		tcsetattr(STDIN_FILENO, TCSANOW, &sa.term);
	}
	free_tree(tree);
	here_del();
	change_sig(tree);
}

void test()
{
	system("leaks minishell");
}

int	main(int argc, char **argv, char **en)
{
	char	**envp;
	t_tree	*tree;
	char	*line;
	t_set	sa;			

	atexit(test);
	//char *hi;
	//hi = (char *)malloc(3000000);
	//hi = 0;
	minishell_sig_setting(&sa.sig, &sa.old_term, &sa.term);
	envp = cp_envp(en);
	unset_oldpath(&envp);
	here_del();
	print_init_msg();
	while (1)
	{
		line = readline("\x1b[38;5;204mminishell-0.1$\x1b[0m ");
		if (!line)
			program_end(sa.old_term);
		else if (!*line)
			free(line);
		else if (*line)
		{
			tree_start(tree, line, envp, sa);
		}
	}
	return (0);
}
