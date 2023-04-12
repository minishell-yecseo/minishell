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

void	sort_list_by_line(t_list **head)
{
	t_list	*tmp;
	int		len;
	int		cnt;
	int		idx;

	cnt = 0;
	len = get_list_len(*head);
	while (cnt < len)
	{
		idx = 0;
		tmp = *head;
		while (idx + 1 < len)
		{
			if (ft_strcmp(tmp->line, tmp->next->line) > 0)
				list_swap_with_next(head, tmp);
			else
				tmp = tmp->next;
			idx++;
		}
		cnt++;
	}
}

void	list_swap_with_next(t_list **head, t_list *node)
{
	t_list	*next_tmp;

	if (!node)
		return ;
	if (node->next == NULL)
		return ;
	if (node == *head)
		*head = node->next;
	next_tmp = node->next->next;
	node->next->next = node;
	if (node->prev)
		(node->prev)->next = node->next;
	node->prev = node->next;
	if (next_tmp)
		next_tmp->prev = node;
	node->next = next_tmp;
}

int	get_list_len(t_list *head)
{
	int	cnt;

	cnt = 0;
	if (!head)
		return (0);
	while (head)
	{
		cnt++;
		head = head->next;
	}
	return (cnt);
}
