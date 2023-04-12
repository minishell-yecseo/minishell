#include "utils.h"

t_list	*lexer(char *line, char **envp)
{
	t_list	*ret;
	char	*replace_line;
	int		syntax;

	syntax = pre_syntax_checker(line);
	if (!syntax)
		return (NULL);
	replace_line = get_line_replace_envp(line, envp);
	syntax = quote_pair_syntax_checker(replace_line);
	if (!syntax)
	{
		free(replace_line);
		return (NULL);
	}
	ret = NULL;
	set_list_from_line(&ret, replace_line);
	free(replace_line);
	build_list_with_space(ret);
	build_list_with_asterisk(&ret);
	syntax = post_syntax_checker(ret);
	if (!syntax)
	{
		free_line_list(ret);
		return (NULL);
	}
	return (ret);
}

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

void	set_list_from_line(t_list **head, char *line)
{
	char	*tmp;
	int		token_len;

	tmp = line;
	token_len = 0;
	while (*tmp)
	{
		if (char_type_for_list(*tmp) == C_REDIR)
			token_len = add_redir(head, tmp);
		else if (char_type_for_list(*tmp) == C_PIPE)
			token_len = add_pipe(head, tmp);
		else if (char_type_for_list(*tmp) == QUOTE)
			token_len = add_quotes(head, tmp);
		else
			token_len = add_word(head, tmp);
		tmp += token_len;
	}
}

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
	int		type;

	len = 0;
	while (line[len])
	{
		type = char_type_for_list(line[len]);
		if (type == WHITE_SPACE || type == C_REDIR || \
				type == C_PIPE || type == QUOTE)
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
