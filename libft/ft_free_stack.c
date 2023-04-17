/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_stack.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:33:21 by yecnam            #+#    #+#             */
/*   Updated: 2023/04/17 16:33:22 by yecnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_stack(t_stack *stack)
{
	t_stack_node	*node;

	if (!stack)
		return ;
	while (stack->size)
	{
		node = ft_pop(stack);
		free(node);
	}
	free(stack);
}
