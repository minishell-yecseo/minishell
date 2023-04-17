/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_stack_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:33:41 by yecnam            #+#    #+#             */
/*   Updated: 2023/04/17 16:33:42 by yecnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_stack_node	*ft_new_stack_node(char quote)
{
	t_stack_node	*node;

	node = (t_stack_node *) ft_calloc(1, sizeof(t_stack_node));
	if (!node)
		return (NULL);
	node->quote = quote;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}
