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
