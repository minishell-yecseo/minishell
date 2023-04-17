/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pop.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:33:44 by yecnam            #+#    #+#             */
/*   Updated: 2023/04/17 16:33:44 by yecnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_stack_node	*ft_pop(t_stack *stack)
{
	t_stack_node	*pop_node;
	t_stack_node	*new_top;

	if (!stack || stack->size == 0)
		return (NULL);
	pop_node = stack->top;
	new_top = stack->top->prev;
	stack->top = new_top;
	stack->size -= 1;
	return (pop_node);
}
