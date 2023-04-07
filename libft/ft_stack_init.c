#include "libft.h"

t_stack	*stack_init(void)
{
	t_stack	*ret;

	ret = (t_stack *) ft_calloc(1, sizeof(t_stack));
	if (!ret)
		return (NULL);
	return (ret);
}
