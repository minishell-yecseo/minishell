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
