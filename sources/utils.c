#include "utils.h"

//test main function
/*
#include <stdio.h>
int	main(int argc, char **argv, char **envp)
{
	char	*line = "cat | cat | ls -al | grep hello | >outfile | nocmd | ls <infile";
	t_tree	*tree;

	// 이제 get_tree에 line 과 envp 넣어주면 tree 를 알아서 빌드해줍니다.
	// 아래와 같이 사용하실 수 있습니다.
	// 하지만 아직 syntax 에러를 처리하지 않았습니다.
	
	tree = get_tree(line, envp);
	traverse(tree, tree->root, &envp);
	free_tree(tree);
	system("leaks a.out");
	return (0);
}
*/
//Not Implemeted yet
t_tree	*get_tree(char *line, char **envp)
{
	t_tree	*tree;
	t_list	*list;
	int		syntax_flag;

	syntax_flag = 1;
	/*
	syntax_flag = pre_syntax_checker(line);
	if (!syntax_flag)
		return (NULL);
	*/
	list = lexer(line, envp);
	if (!list)
		return (NULL);
	syntax_flag = post_syntax_checker(list);
	if (!syntax_flag)
		return (NULL);
	tree = tree_builder(list);
	free_line_list(list);
	return (tree);
}

void	free_line_list(t_list *head)
{
	t_list	*cur;
	t_list	*tmp;

	cur = head;
	while (cur)
	{
		if (cur->type == L_WORD)
			free(cur->line);
		tmp = cur;
		cur = cur->next;
		free(tmp);
	}
}
