/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tokenizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saseo <saseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:31:16 by saseo             #+#    #+#             */
/*   Updated: 2023/04/03 19:08:41 by saseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

//cat Makefile | >a |<a ls -al >b < c | <d grep Makefile >e >f | >last cat | cat

int	add_redir(t_list **list, char *line, char **envp)
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
	ft_lstadd_back(list, new);
	len = ft_strlen(new->line);
	return (len);
}

int	add_pipe(t_list **list, char *line, char **envp)
{
	t_list	*new;

	new = ft_lstnew(L_PIPE, "|");
	if (!new)
		exit(0);
	ft_lstadd_back(list, new);
	return (1);
}

int	add_quotes(t_list **list, char *line, char **envp)
{
	t_list	*new;
	char	*new_line;
	char	quote_type;
	int		len;

	len = 1;
	quote_type = *line;
	line++;
	while (line[len] == quote_type || line[len] == '\0')
		len++;
	new_line = ft_substr(line, 0, len);
	if (!new_line)
		exit(0);
	new = ft_lstnew(L_WORD, new_line);
	if (!new)
		exit(0);
	ft_lstadd_back(list, new);
	return (len);
}

int	add_word(t_list **list, char *line, char **envp)
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
	ft_lstadd_back(list, new);
	return (len);
}
