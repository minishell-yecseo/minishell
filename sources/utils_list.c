#include "utils.h"

t_list	*ft_lstnew(t_l_type type, char *line)
{
	t_list	*ret;

	ret = (t_list *) ft_calloc(sizeof(t_list));
	if (!ret)
		return (NULL);
	ret->type = type;
	ret->line = line;
	ret->prev = NULL;
	ret->next = NULL;
	return (ret);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*lstlast;

	if (new == NULL || lst == NULL)
		return ;
	lstlast = ft_lstlast(*lst);
	if (lstlast == NULL)
		*lst = new;
	else
	{
		new->prev = lstlast;
		lstlast->next = new;
	}
}

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (lst);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
