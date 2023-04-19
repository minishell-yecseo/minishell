/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:30:58 by saseo             #+#    #+#             */
/*   Updated: 2023/04/19 13:54:33 by yecnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

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
	node->next->prev = node->prev;
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
