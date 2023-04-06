#include "utils.h"

//test main function
/*
#include <stdio.h>
int	main(int argc, char **argv, char **envp)
{
	char	*line = "\"ls -al $? $file\"|'cat' '$file'>out|nocmd \"\'$var2\'\"";
	t_list	*list;
	int		idx = 0;

	printf("%s\n", line);
	list = lexer(line, envp);
	while (list)
	{
		printf("[%s]-", list->line);
		idx++;
		list = list->next;
	}
	printf("\n");
	return 0;
}
*/

//Not Implemeted yet
t_tree	*get_tree(char *line, char **envp)
{
	t_tree	*tree;
	t_list	*list;

	// lexer			: return list of lexical_tokens
	// syntax checker	: return 0 if syntax has no error else -1
	// tree builder		: return pointer of tree
	//					: each level call their lower process functs recursively

	list = lexer(line, envp);//need to implement
	if (!syntax(&list))
		return (NULL);
	tree = tree_builder(list);
	return (tree);
}

int	syntax(t_list **head)
{
	int	ret;

	ret = 1;
	free_line_list(*head);//need to implement
	line_syn_err();//need to implement
	return (ret);
}

void	line_syn_err(void)
{
	char	*msg;

	msg = "minishell: line has syntax error!\n";
	g_last_exit_code = 2;
	write(2, msg, ft_strlen(msg));
}

void	free_line_list(t_list *head)
{
	t_list	*cur;
	t_list	*tmp;

	cur = head;
	while (cur)
	{
		free(cur->line);
		tmp = cur;
		cur = cur->next;
		free(tmp);
	}
}
