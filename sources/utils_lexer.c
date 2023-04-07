#include "utils.h"

t_list	*lexer(char *line, char **envp)
{
	t_list	*ret;
	char	*replace_line;

	if (quote_pair_syntax_checker(line) == 0)
		return (NULL);
	replace_line = get_line_replace_envp(line, envp);
	if (quote_pair_syntax_checker(replace_line) == 0)
		return (NULL);
	ret = NULL;
	set_list_from_line(&ret, replace_line);
	build_list_with_space(ret);
	free(replace_line);
	return (ret);
}

void	build_list_with_space(t_list *head)
{
	// is_end가 0이면 is_end가 1인 토큰을 찾아서
	// 그 사이의 line들을 맨 앞 리스트의 line에 붙여준다.
	// is_end 가 1인 마지막 리스트까지는 모두 삭제
	// is_end == 0인 리스트의 next는 is_end ==1 인 리스트의 next로 바꿔준다.
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
			exit(0);
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
		exit(0);
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
		exit(0);
	if (!ft_lstadd_back(head, lst))
		exit(0);
	lst->is_end = 1;
	return (1);
}

int	add_quotes(t_list **head, char *line)
{
	t_list	*new;
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
		exit(0);
	if (!ft_lstadd_back(head, ft_lstnew(L_WORD, new_line)))
		exit(0);
	type = char_type_for_list(line[len + 1]);
	if (type == QUOTE || type == OTHER)
		ft_lstlast(*head)->is_end = 0;
	else
		ft_lstlast(*head)->is_end = 1;
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
		if (type == WHITE_SPACE || type == C_REDIR ||\
				type == C_PIPE || type == QUOTE)
			break ;
		len++;
	}
	if (len == 0)
		return (1);
	new_line = ft_substr(line, 0, len);
	if (!new_line)
		exit(0);
	if (!ft_lstadd_back(head, ft_lstnew(L_WORD, new_line)))
		exit(0);
	if (char_type_for_list(line[len]) == QUOTE)
		ft_lstlast(*head)->is_end = 0;
	else
		ft_lstlast(*head)->is_end = 1;
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
