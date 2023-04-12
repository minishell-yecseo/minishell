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
	char **envp;
	t_node	*root;
	t_list	*head;
	t_tree	*tree;
	char	*line;
	struct sigaction	sig;
	struct termios		old_term;
	struct termios		term;

	// 이제 get_tree에 line 과 envp 넣어주면 tree 를 알아서 빌드해줍니다.
	// 아래와 같이 사용하실 수 있습니다.
	// 하지만 아직 syntax 에러를 처리하지 않았습니다.
	
	minishell_sig_setting(&sig, &old_term, &term);
	envp = cp_envp(en);
	unset_oldpath(&envp);
	print_init_msg();
	while (1)
	{
		line = readline("\x1b[38;5;204mminishell-0.1$\x1b[0m ");
		if (!line)
			program_end(old_term);
		else if (!*line)
			;
		else
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
	return 0;
}

static void	set_test_list(t_list **head)
{
	/*
	 * 이 문장을 넣은 것입니닷.
	 * cat Makefile | >a |<a ls -al >b < c | <d grep Makefile >e >f | >last cat | cat
	 *
	 * ft_lstnew(t_l_type type, char *line)
	 * => t_l_type 에는 세 종류가 있습니다.
	 *		L_PIPE, L_REDIR, L_WORD
	 */

	*head = ft_lstnew(L_WORD, "cata");
	//ft_lstadd_back(head, ft_lstnew(L_PIPE, "|"));
	//ft_lstadd_back(head, ft_lstnew(L_WORD, "cd"));
	//ft_lstadd_back(head, ft_lstnew(L_WORD, ".."));
	////ft_lstadd_back(head, ft_lstnew(L_WORD, "exit"));
	////ft_lstadd_back(head, ft_lstnew(L_WORD, "100"));
	////ft_lstadd_back(head, ft_lstnew(L_WORD, ""));
	//ft_lstadd_back(head, ft_lstnew(L_PIPE, "|"));
	//ft_lstadd_back(head, ft_lstnew(L_WORD, "export"));

	//ft_lstadd_back(head, ft_lstnew(L_PIPE, "|"));
	//ft_lstadd_back(head, ft_lstnew(L_WORD, "cat"));

	//ft_lstadd_back(head, ft_lstnew(L_PIPE, "|"));
	//ft_lstadd_back(head, ft_lstnew(L_WORD, "wc"));
	//ft_lstadd_back(head, ft_lstnew(L_WORD, "-w"));
	//ft_lstadd_back(head, ft_lstnew(L_REDIR, "<"));
	//ft_lstadd_back(head, ft_lstnew(L_WORD, "a"));
	//ft_lstadd_back(head, ft_lstnew(L_WORD, "ls"));
	//ft_lstadd_back(head, ft_lstnew(L_WORD, "-al"));
	//ft_lstadd_back(head, ft_lstnew(L_REDIR, ">"));
	//ft_lstadd_back(head, ft_lstnew(L_WORD, "b"));
	//ft_lstadd_back(head, ft_lstnew(L_REDIR, "<"));
	//ft_lstadd_back(head, ft_lstnew(L_WORD, "c"));

	//ft_lstadd_back(head, ft_lstnew(L_PIPE, "|"));
	//ft_lstadd_back(head, ft_lstnew(L_REDIR, "<"));
	//ft_lstadd_back(head, ft_lstnew(L_WORD, "d"));
	//ft_lstadd_back(head, ft_lstnew(L_WORD, "grep"));
	//ft_lstadd_back(head, ft_lstnew(L_WORD, "Makefile"));
	//ft_lstadd_back(head, ft_lstnew(L_REDIR, ">"));
	//ft_lstadd_back(head, ft_lstnew(L_WORD, "e"));
	//ft_lstadd_back(head, ft_lstnew(L_REDIR, ">"));
	//ft_lstadd_back(head, ft_lstnew(L_WORD, "f"));

	//ft_lstadd_back(head, ft_lstnew(L_PIPE, "|"));
	//ft_lstadd_back(head, ft_lstnew(L_REDIR, ">"));
	//ft_lstadd_back(head, ft_lstnew(L_WORD, "last"));
	//ft_lstadd_back(head, ft_lstnew(L_WORD, "cat"));

	//ft_lstadd_back(head, ft_lstnew(L_PIPE, "|"));
	//ft_lstadd_back(head, ft_lstnew(L_WORD, "cat"));
}
