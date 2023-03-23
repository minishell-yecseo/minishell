#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include "tree.h"

static void	setting(t_tree *tree);

int	main(int argc, char **argv, char **envp)
{
	t_tree	*tree;
	int status;
	int pid;
	// 정보들을 담고 있는 cont 구조체 생성.
	// 모든 type 에서 각기 필요한 정보를
	// cont 구조체를 참고하여 사용하면 됨.
	//
	// 일단 당장 연습용으로
	// 실행부는 tree.c 에 있는 traverse 함수를 수정하여
	// 사용하면 됩니다.

	tree = init_tree();
	setting(tree);
	traverse(tree, tree->head);
	while ((pid = wait(&status)) != -1)
		;
	return 0;
}

static void	setting(t_tree *tree)
{
	t_node	*tmp;
	char	**args1;
	char	**args2;

	tree->head = create_node(PIPE);
	tree->head->cont.fds[0] = 0;
	tree->head->cont.fds[0] = 1;
	tree->head->cont.is_pipe = 1;

	tmp = tree->head;
	tree->size += 1;
	insert_left(tree, tmp, create_node(CMD));
	tmp = tmp->left;

	insert_left(tree, tmp, create_node(REDIR));
	insert_right(tree, tmp, create_node(SIMPLE_CMD));
	(tmp->left->cont).redir_type = OUT_A;
	(tmp->left->cont).file_name = "test.txt";
	tmp->left->cont.fd = -1;

	tmp->right->cont.path = "/bin/cat";
	args1 = (char **)malloc(sizeof(char *) * 3);
	args1[0] = "cat";
	args1[1] = "main.c";
	args1[2] = 0;

	tmp->right->cont.args = args1;

	tmp = tree->head;
	insert_right(tree, tmp, create_node(PIPE));
	tmp = tmp->right;

	insert_left(tree, tmp, create_node(CMD));
	tmp = tmp->left;//cmd

	insert_right(tree, tmp, create_node(SIMPLE_CMD));//cmd->right
	tmp->right->cont.path = "/usr/bin/grep";//cmd->right 의 contents
	args2 = (char **)malloc(sizeof(char *) * 3);
	args2[0] = "grep";
	args2[1] = "main";
	args2[2] = NULL;
	tmp->right->cont.args = args2;
}
