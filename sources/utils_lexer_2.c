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
	char	*new_line;
	char	quote_type;
	int		len;
	int		type;

	len = 1;
	quote_type = *line;
	while (line[len] != quote_type && line[len] != '\0')
		len++;
	new_line = ft_substr(line + 1, 0, len - 1);
	if (!new_line)
		malloc_fail();
	if (!ft_lstadd_back(head, ft_lstnew(L_WORD, new_line)))
		malloc_fail();
	type = char_type_for_list(line[len + 1]);
	if (type == QUOTE || type == OTHER)
		ft_lstlast(*head)->is_end = 0;
	else
		ft_lstlast(*head)->is_end = 1;
	ft_lstlast(*head)->is_quote = 1;
	len++;
	return (len);
}

int	add_word(t_list **head, char *line)
{
	char	*new_line;
	int		len;
	int		c;

	len = 0;
	while (line[len])
	{
		c = char_type_for_list(line[len]);
		if (c == WHITE_SPACE || c == C_REDIR || c == C_PIPE || c == QUOTE)
			break ;
		len++;
	}
	if (len == 0)
		return (1);
	new_line = ft_substr(line, 0, len);
	if (!new_line)
		malloc_fail();
	if (!ft_lstadd_back(head, ft_lstnew(L_WORD, new_line)))
		malloc_fail();
	if (char_type_for_list(line[len]) == QUOTE)
		ft_lstlast(*head)->is_end = 0;
	else
		ft_lstlast(*head)->is_end = 1;
	ft_lstlast(*head)->is_quote = 0;
	return (len);
}
