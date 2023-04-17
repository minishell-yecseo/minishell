/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:33:47 by yecnam            #+#    #+#             */
/*   Updated: 2023/04/17 16:33:48 by yecnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_push(t_stack *stack, char quote)
{
	t_stack_node	*new_node;

	if (!stack)
		return ;
	new_node = ft_new_stack_node(quote);
	if (!new_node)
		return ;
	if (stack->top)
		stack->top->next = new_node;
	new_node->prev = stack->top;
	stack->top = new_node;
	stack->size += 1;
}
