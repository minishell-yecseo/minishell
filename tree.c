#include "tree.h"

t_tree	*init_tree(void)
{
	t_tree	*tree;

	tree = (t_tree *) malloc(sizeof(t_tree));
	if (!tree)
		exit(0);
	tree->head = NULL;
	tree->size = 0;
	return (tree);
}

t_node	*create_node(t_token type)
{
	t_node	*node;

	node = (t_node *) malloc(sizeof(t_node));
	if (!node)
		exit(0);
	node->type = type;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

void	insert_left(t_node *parent, t_node *child)
{
	parent->left = child;
}

void	insert_right(t_node *parent, t_node *child)
{
	parent->right = child;
}

int	traverse(t_tree *tree, t_node *cur, char ***envp)
{
	if (!tree)
		return (0);
	if (!cur)
		return (0);
	print_token_type(cur);
	print_cont(&(cur->cont), cur->type);
	exe_cur(tree, cur, envp);
	traverse(tree, cur->left, envp);
	traverse(tree, cur->right, envp);
	return (0);
}

void	print_token_type(t_node *node)
{
	if (node->type == PIPE)
		printf("PIPE::");
	else if (node->type == CMD)
		printf("CMD::");
	else if (node->type == NO_CMD)
		printf("NO_CMD::");
	else if (node->type == REDIR)
		printf("REDIR::");
	else if (node->type == SIMPLE_CMD)
		printf("SIMPLE_CMD::");
}

void	print_cont(t_cont *cont, t_token type)
{
	char	**tmp;

	if (type == PIPE)
	{
		printf("\tpipe fds :%d, %d\n", (cont->fds)[0], (cont->fds)[1]);
		printf("\tis_pipe :%d\n\n", cont->is_pipe);
	}
	else if (type == CMD)
		printf("\tnone\n\n");
	else if (type == NO_CMD)
		printf("\tnone\n\n");
	else if (type == REDIR)
	{
		printf("\tredirection type :");
		if (cont->redir_type == IN)
			printf("IN\n");
		else if (cont->redir_type == HERE_DOC)
			printf("HERE_DOC\n");
		else if (cont->redir_type == OUT_T)
			printf("OUT_T\n");
		else
			printf(" OUT_A\n");
		printf("\tfile_name :%s\n", cont->file_name);
		printf("\tfd :%d\n\n", cont->fd);
	}
	else if (type == SIMPLE_CMD)
	{
		tmp = cont->args;
		printf("\n\tpath :%s\n", cont->path);
		printf("\targs :");
		while (*tmp)
		{
			printf("%s ", *tmp);
			tmp++;
		}
		printf("\n\n");
	}
}
