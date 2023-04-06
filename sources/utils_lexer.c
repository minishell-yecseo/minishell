#include "utils.h"

t_list	*lexer(char *line, char **envp)
{
	t_list	*ret;
	char	*replace_line;

	replace_line = get_line_replace_envp(line, envp);
	ret = NULL;
	set_list_from_line(&ret, replace_line);
	free(replace_line);
	if (!ret)
		exit(0);
	return (ret);
}

void	set_list_from_line(t_list **head, char *line)
{
	char	*tmp;
	int		token_len;

	tmp = line;
	token_len = 0;
	while (*tmp)
	{
		if (*tmp == '<' || *tmp == '>')
			token_len = add_redir(head, tmp);
		else if (*tmp == '|')
			token_len = add_pipe(head, tmp);
		else if (*tmp == '\'' || *tmp == '\"')
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
	ft_lstadd_back(head, new);
	len = ft_strlen(new->line);
	return (len);
}

int	add_pipe(t_list **head, char *line)
{
	t_list	*new;

	new = ft_lstnew(L_PIPE, "|");
	if (!new)
		exit(0);
	ft_lstadd_back(head, new);
	return (1);
}

int	add_quotes(t_list **head, char *line)
{
	t_list	*new;
	char	*new_line;
	char	quote_type;
	int		len;

	len = 1;
	quote_type = *line;
	while (line[len] != quote_type && line[len] != '\0')
		len++;
	new_line = ft_substr(line + 1, 0, len - 1);
	if (!new_line)
		exit(0);
	new = ft_lstnew(L_WORD, new_line);
	if (!new)
		exit(0);
	ft_lstadd_back(head, new);
	len++;
	return (len);
}

int	add_word(t_list **head, char *line)
{
	t_list	*new;
	char	*new_line;
	int		len;

	len = 0;
	while (line[len])
	{
		if (line[len] == ' ' || (line[len] > 8 && line[len] < 14))
			break ;
		if (line[len] == '<' || line[len] == '>' || line[len] == '|')
			break ;
		len++;
	}
	if (len == 0)
		return (1);
	new_line = ft_substr(line, 0, len);
	if (!new_line)
		exit(0);
	new = ft_lstnew(L_WORD, new_line);
	if (!new)
		exit(0);
	ft_lstadd_back(head, new);
	return (len);
}
