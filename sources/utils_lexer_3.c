#include "utils.h"

void	build_list_with_space(t_list *head)
{
	t_list	*tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->is_end == 0)
			tokens_to_one(tmp);
		tmp = tmp->next;
	}
}

void	tokens_to_one(t_list *list)
{
	t_list	*last;
	t_list	*tmp;
	char	*new_line;

	last = list->next;
	while (last && last->is_end == 0)
		last = last->next;
	tmp = list->next;
	while (tmp && tmp != last->next)
	{
		new_line = ft_strjoin(list->line, tmp->line);
		free(list->line);
		if (!new_line)
			malloc_fail();
		list->line = new_line;
		tmp = tmp->next;
	}
	tmp = last->next;
	free_sub_list(list->next, last);
	list->next = tmp;
	list->is_end = 1;
}

void	free_sub_list(t_list *start, t_list *last)
{
	t_list	*lst;
	t_list	*tmp;

	lst = start;
	while (lst != last)
	{
		if (lst->type == L_WORD)
			free(lst->line);
		tmp = lst->next;
		free(lst);
		lst = tmp;
	}
	if (last && last->type == L_WORD)
		free(last->line);
	if (last)
		free(last);
}

int	char_type_for_list(char c)
{
	if (c == '\0')
		return (ZERO);
	else if (c == ' ' || c > 8 && c < 14)
		return (WHITE_SPACE);
	else if (c == '<' || c == '>')
		return (C_REDIR);
	else if (c == '|')
		return (C_PIPE);
	else if (c == '\'' || c == '\"')
		return (QUOTE);
	else
		return (OTHER);
}

void	set_quotes_list_end_var(t_list *quote_list, char *line, int len)
{
	int	type;

	type = char_type_for_list(line[len]);
	if (type == ZERO)
		quote_list->is_end = 1;
	else if (type != ZERO)
	{
		type = char_type_for_list(line[len + 1]);
		if (type == QUOTE || type == OTHER)
			quote_list->is_end = 0;
		else
			quote_list->is_end = 1;
	}
}
