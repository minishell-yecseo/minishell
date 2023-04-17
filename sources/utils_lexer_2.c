#include "utils.h"

int	add_redir(t_list **head, char *line)
{
	t_list	*new;
	int		len;

	if (*line == '<' && *(line + 1) != '<')
		new = ft_lstnew(L_REDIR, "<");
	else if (*line == '<' && *(line + 1) == '<')
		new = ft_lstnew(L_REDIR, "<<");
	else if (*line == '>' && *(line + 1) != '>')
		new = ft_lstnew(L_REDIR, ">");
	else if (*line == '>' && *(line + 1) == '>')
		new = ft_lstnew(L_REDIR, ">>");
	if (!new)
		malloc_fail();
	new->is_end = 1;
	ft_lstadd_back(head, new);
	len = ft_strlen(new->line);
	return (len);
}

int	add_pipe(t_list **head, char *line)
{
	t_list	*lst;

	lst = ft_lstnew(L_PIPE, "|");
	if (!lst)
		malloc_fail();
	ft_lstadd_back(head, lst);
	lst->is_end = 1;
	return (1);
}

int	add_quotes(t_list **head, char *line)
{
	t_list	*new_list;
	char	*new_line;
	char	quote_type;
	int		len;
	int		type;

	len = get_quotes_len_for_list(line);
	new_line = ft_substr(line, 1, len - 1);
	if (!new_line)
		malloc_fail();
	new_list = ft_lstnew(L_WORD, new_line);
	if (!new_list)
		malloc_fail();
	ft_lstadd_back(head, new_list);
	set_quotes_list_end_var(new_list, line, len);
	new_list->is_quote = 1;
	len++;
	return (len);
}

int	add_word(t_list **head, char *line)
{
	t_list	*new_list;
	char	*new_line;
	int		len;

	len = get_word_len_for_list(line);
	if (len == 0)
		return (1);
	new_line = ft_substr(line, 0, len);
	if (!new_line)
		malloc_fail();
	new_list = ft_lstnew(L_WORD, new_line);
	if (!new_list)
		malloc_fail();
	ft_lstadd_back(head, new_list);
	set_word_list_end_var(new_list, line, len);
	new_list->is_quote = 0;
	return (len);
}
