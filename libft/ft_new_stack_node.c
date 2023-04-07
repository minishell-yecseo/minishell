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
