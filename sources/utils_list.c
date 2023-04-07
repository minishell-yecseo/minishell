#include "utils.h"

t_list	*ft_lstnew(t_l_type type, char *line)
{
	t_list	*ret;

	ret = (t_list *) ft_calloc(1, sizeof(t_list));
	if (!ret)
		return (NULL);
	ret->type = type;
	ret->line = line;
	ret->prev = NULL;
	ret->next = NULL;
	return (ret);
}

int	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*lstlast;

	if (lst == NULL || new == NULL)
		return (0);
	lstlast = ft_lstlast(*lst);
	if (lstlast == NULL)
		*lst = new;
	else
	{
		new->prev = lstlast;
		lstlast->next = new;
	}
	return (1);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (lst);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
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
	if (lst->type == C_PIPE)
		printf("PIPE:");
	else if (lst->type == C_REDIR)
		printf("REDIR:");
	else if (lst->type == OTHER)
		printf("OTHER:");
	else if (lst->type == QUOTE)
		printf("QUOTE:");
	else if (lst->type == ZERO)
		printf("ZERO:");
}
