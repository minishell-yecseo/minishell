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

	// 여러 번 참조하는 거 좀 오바같은데
	// 어차피 실행부에서는 최대 2 번 참조하긴 함
	// ex) node->(union type)->(attribute)
	// 아니면, 아예 모든 속성을 갖는 구조체 생성해서
	// 타입 확인 후 필요한 속성만 쓰는 방법도 있음.
	//
	// 일단 당장 연습용으로
	// 실행부는 tree.c 에 있는 traverse 함수를 수정하여
	// 사용하면 됩니다.

	tree = init_tree();
	setting(tree);
	traverse(tree, tree->head);
	return 0;
}

static void	setting(t_tree *tree)
{
	t_node	*tmp;
	char	**args1;
	char	**args2;

	tree->head = create_node(PIPE);
	tree->head->cont.pipe.fds[0] = 0;
	tree->head->cont.pipe.fds[0] = 1;
	tree->head->cont.pipe.is_pipe = 1;

	tmp = tree->head;
	tree->size += 1;
	insert_left(tree, tmp, create_node(CMD));
	tmp = tmp->left;
	tmp->cont.cmd.none = 0;

	insert_left(tree, tmp, create_node(REDIR));
	insert_right(tree, tmp, create_node(SIMPLE_CMD));
	(tmp->left->cont.redir).type = IN;
	(tmp->left->cont.redir).file_name = "test.txt";
	tmp->left->cont.redir.fd = -1;

	tmp->right->cont.simple_cmd.path = "/bin/cat";
	args1 = (char **)malloc(sizeof(char *) * 2);
	args1[0] = "cat";
	args1[1] = NULL;
	tmp->right->cont.simple_cmd.args = args1;

	tmp = tree->head;
	insert_right(tree, tmp, create_node(CMD));
	tmp = tmp->right;
	tmp->cont.cmd.none = 0;

	insert_right(tree, tmp, create_node(SIMPLE_CMD));
	tmp->right->cont.simple_cmd.path = "/bin/grep";
	args2 = (char **)malloc(sizeof(char *) * 3);
	args2[0] = "grep";
	args2[1] = "hello";
	args2[2] = NULL;
	tmp->right->cont.simple_cmd.args = args2;
}
