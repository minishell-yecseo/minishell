#include "utils.h"

void	print_token_type(t_node *node)
{
	printf("\x1b[38;5;33m");
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
	printf("\x1b[0m");
}

void	print_cont(t_cont *cont, t_token type)
{
	char	**tmp;

	if (type == PIPE)
		printf("\n");
	else if (type == CMD)
		printf("\t(CMD)\n\n");
	else if (type == NO_CMD)
		printf("\tNO_CMD\n\n");
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
		printf("\tfile_name :[%s]\n", cont->file_name);
		printf("\tfd :%d\n\n", cont->fd);
	}
	else if (type == SIMPLE_CMD)
	{
		tmp = cont->args;
		printf("\n\tpath :%s\n", cont->path);
		printf("\targs :");
		while (*tmp)
		{
			printf("[%s] ", *tmp);
			tmp++;
		}
		printf("\n\n");
	}
}

void	ft_print_list(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	while (tmp)
	{
		print_list_type(tmp);
		printf("[%s]", tmp->line);
		printf("(%d)\n", tmp->is_end);
		tmp = tmp->next;
	}
	printf("\n");
}

void	print_list_type(t_list *lst)
{
	if (lst->type == L_PIPE)
		printf("PIPE:");
	else if (lst->type == L_REDIR)
		printf("REDIR:");
	else if (lst->type == L_WORD)
		printf("WORD:");
}
