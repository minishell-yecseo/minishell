#include "minishell.h"

static void	set_test_list(t_list **head);

void	unset_oldpath(char ***envp)
{
	*envp = oldpwd_envp(envp, "OLDPWD");
}

void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf(">\n");
		rl_replace_line("", 1);
		rl_on_new_line();
    	rl_redisplay();
	}
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
	struct termios term;
	char **envp;
	// 정보들을 담고 있는 cont 구조체 생성.
	// 모든 type 에서 각기 필요한 정보를
	// cont 구조체를 참고하여 사용하면 됨.
	//
	// 일단 당장 연습용으로
	// 실행부는 tree.c 에 있는 traverse 함수를 수정하여
	// 사용하면 됩니다.

	//터미널 및 시그널 처리
	//tcgetattr(STDIN_FILENO, &term);
    //term.c_lflag &= ~(ECHOCTL);
    //tcsetattr(STDIN_FILENO, TCSANOW, &term);
	//signal(SIGINT, sigint_handler);
	//signal(SIGQUIT, SIG_IGN); 

	t_node	*root;
	t_list	*head;
	t_tree	*tree;
	char	*line; //= "\"ls -al $? $file\"|'cat' '$file'>out|nocmd \"\'$var2\'\"";

	// 이제 get_tree에 line 과 envp 넣어주면 tree 를 알아서 빌드해줍니다.
	// 아래와 같이 사용하실 수 있습니다.
	// 하지만 아직 syntax 에러를 처리하지 않았습니다.
	
	envp = cp_envp(en);
	unset_oldpath(&envp);
	
	while (1)
	{
		line = readline("> ");
		tree = get_tree(line, envp);

		tree->stdfds[0] = dup(0);
		tree->stdfds[1] = dup(1);
		//int i = 0;
		//while (envp[i])
		//{
		//	printf("%s\n", envp[i]);
		//	i++;
		//}
		traverse(tree, tree->root, &envp);
		wait_forks(tree);
		//printf("\n\n\n\n");
		//i = 0;
		//while (envp[i])
		//{
		//	printf("%s\n", envp[i]);
		//	i++;
		//}
		//dup2(tree->stdfds[0], 0);
		dup2(tree->stdfds[1], 1);
		close(tree->stdfds[0]);
		close(tree->stdfds[1]);

		free_tree(tree);
		printf("$? : %d\n", g_last_exit_code);
		free(line);
	}
	
	//char	buffer[100];
	//read(0, buffer, 100);
	//printf("%s\n", buffer);
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
