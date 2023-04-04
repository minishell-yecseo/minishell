#include "utils.h"
#include "minishell.h"

static void	set_test_list(t_list **head);
int	g_last_exit_code;

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

	t_tree	*tree;
	t_node	*root;
	t_list	*head;

	tree = init_tree();
	set_test_list(&head);

	root = create_node(PIPE);
	tree->head = root;
	set_pipe(root, head->next, ft_lstlast(head));

	tree->stdfds[0] = dup(0);
	tree->stdfds[1] = dup(1);
	envp = cp_envp(en);
	unset_oldpath(&envp);
	int i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	traverse(tree, tree->head, &envp);
	
	printf("\n\n\n\n");
	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	wait_forks(tree);
	//dup2(tree->stdfds[0], 0);
	dup2(tree->stdfds[1], 1);
	close(tree->stdfds[0]);
	close(tree->stdfds[1]);
	printf("$? : %d\n", g_last_exit_code);
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

	*head = ft_lstnew(L_PIPE, "|");
	ft_lstadd_back(head, ft_lstnew(L_WORD, "cd"));
	ft_lstadd_back(head, ft_lstnew(L_WORD, "headers"));
	//ft_lstadd_back(head, ft_lstnew(L_WORD, "abcdedaaa"));
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