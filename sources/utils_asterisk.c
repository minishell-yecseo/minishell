/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_asterisk.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saseo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:30:15 by saseo             #+#    #+#             */
/*   Updated: 2023/04/17 16:30:18 by saseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	build_list_with_asterisk(t_list **head)
{
	t_list	*node;
	t_list	*aster_list;
	t_list	*next;
	int		heredoc;
	int		status;

	node = *head;
	while (node)
	{
		next = node->next;
		aster_list = NULL;
		set_here_doc_flag(node, &heredoc);
		if (node->type == L_WORD && node->is_quote == 0 && !heredoc)
		{
			if (ft_strcmp("*", node->line) == 0 || \
					ft_strcmp("./*", node->line) == 0)
				aster_list = get_entry_name_list(&status);
		}
		if (!status)
			return (0);
		if (aster_list)
			join_aster_list(head, node, aster_list);
		node = next;
	}
	return (1);
}

void	set_here_doc_flag(t_list *node, int *is_next_to_heredoc)
{
	if (node == NULL)
		return ;
	if (node->type == L_REDIR && ft_strcmp(node->line, "<<") == 0)
		*is_next_to_heredoc = 1;
	else
		*is_next_to_heredoc = 0;
}

void	join_aster_list(t_list **head, t_list *node, t_list *aster_list)
{
	if (node == *head)
		*head = aster_list;
	else
	{
		if (node->prev)
			node->prev->next = aster_list;
		if (node->next)
			node->next->prev = ft_lstlast(aster_list);
		ft_lstlast(aster_list)->next = node->next;
	}
	free(node->line);
	free(node);
}

t_list	*get_entry_name_list(int *status)
{
	t_list			*ret;
	struct dirent	*dp;
	DIR				*dir;

	ret = NULL;
	dir = opendir(".");
	if (!dir)
	{
		*status = 0;
		dir_open_err();
		return (NULL);
	}
	dp = readdir(dir);
	while (dp != NULL)
	{
		if (*(dp->d_name) != '.')
			dup_and_add_list_entry_name(&ret, dp->d_name);
		dp = readdir(dir);
	}
	closedir(dir);
	*status = 1;
	sort_list_by_line(&ret);
	return (ret);
}

void	dup_and_add_list_entry_name(t_list **head, char *name)
{
	char	*line;
	t_list	*node;

	line = ft_strdup(name);
	if (!line)
		malloc_fail();
	node = ft_lstnew(L_WORD, line);
	if (!node)
		malloc_fail();
	ft_lstadd_back(head, node);
}
