#include "utils.h"
#include "minishell.h"

static void	setting(t_tree *tree);
int	g_last_exit_code;

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
	tree->fds[0] = dup(0);
	tree->fds[1] = dup(1);
	envp = cp_envp(en);
	int i = 0;
	//while (envp[i])
	//{
	//	printf("%s\n", envp[i]);
	//	i++;
	//}
	traverse(tree, tree->head, &envp);
	wait_forks(tree);
	dup2(tree->stdfds[0], 0);
	dup2(tree->stdfds[1], 1);
	printf("$? : %d\n", g_last_exit_code);
	return 0;
}

//static void	setting(t_tree *tree)
//{
//	t_node	*tmp;
//	char	**args1;
//	char	**args2;

//	tree->head = create_node(PIPE);
//	tree->head->cont.fds[0] = 0;
//	tree->head->cont.fds[0] = 1;
//	tree->head->cont.is_pipe = 1;

//	tmp = tree->head;
//	tree->size += 1;
//	insert_left(tree, tmp, create_node(CMD));
//	tmp = tmp->left;

//	//insert_left(tree, tmp, create_node(REDIR));
//	insert_right(tree, tmp, create_node(SIMPLE_CMD));
//	//(tmp->left->cont).redir_type = OUT_T;
//	//(tmp->left->cont).file_name = "a";
//	//tmp->left->cont.fd = -1;

//	tmp->right->cont.path = 0;
//	args1 = (char **)malloc(sizeof(char *) * 5);
//	args1[0] = "echo";
//	args1[1] = "-nnnndnn";
//	args1[2] = "as\n\n\ndf";
//	args1[3] = 0;

//	tmp->right->cont.args = args1;

//	tmp = tree->head;
//	insert_right(tree, tmp, create_node(PIPE));
//	tmp = tmp->right;

//	insert_left(tree, tmp, create_node(CMD));
//	tmp = tmp->left;//cmd

//	insert_right(tree, tmp, create_node(SIMPLE_CMD));//cmd->right
//	tmp->right->cont.path = 0;//"/bin/ls";//cmd->right 의 contents
//	args2 = (char **)malloc(sizeof(char *) * 6);
//	args2[0] = "./asdf";
//	args2[1] = 0;
//	args2[3] = "asdf";
//	args2[4] = "aasdfafd";
//	args2[5] = 0;
//	tmp->right->cont.args = args2;
//}
