/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tree_build_2_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:31:33 by saseo             #+#    #+#             */
/*   Updated: 2023/04/18 18:44:21 by yecnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	**get_args(t_list *start, t_list *last)
{
	char	**ret;
	t_list	*tmp;
	int		size;
	int		idx;

	size = 1;
	tmp = start;
	while (tmp != last)
	{
		tmp = tmp->next;
		size++;
	}
	ret = (char **) ft_calloc((size + 1), sizeof(char *));
	if (!ret)
		malloc_fail();
	ret[size] = NULL;
	idx = 0;
	while (idx < size)
	{
		ret[idx] = ft_strdup(start->line);
		if (!ret[idx++])
			malloc_fail();
		start = start->next;
	}
	return (ret);
}

int	get_list_range_size(t_list *start, t_list *last)
{
	int	size;

	size = 1;
	while (start != last)
	{
		start = start->next;
		size++;
	}
	if (last->type == L_PIPE)
		size--;
	return (size);
}

int	get_redir_num_in_range(t_list *start, t_list *last)
{
	int	num;

	num = 0;
	while (start != last)
	{
		if (start->type == L_REDIR)
			num++;
		start = start->next;
	}
	return (num);
}

t_list	*get_word_start_list(t_list *start, t_list *last, int redir_num)
{
	t_list	*tmp;

	tmp = start;
	if (redir_num == 0)
		return (start);
	while (tmp != last)
	{
		if (tmp->type == L_WORD)
		{
			if (tmp->prev == NULL || tmp->prev->type == L_WORD || \
				tmp->prev->type == L_PIPE)
				break ;
		}
		tmp = tmp->next;
	}
	return (tmp);
}

t_list	*get_word_end_list(t_list *start, t_list *last)
{
	t_list	*end;

	end = start;
	while (end != last)
	{
		if (end->next == NULL || end->next->type == L_PIPE \
			|| end->next->type == L_REDIR)
			break ;
		end = end->next;
	}
	return (end);
}
