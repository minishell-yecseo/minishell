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
