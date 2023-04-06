#include "minishell.h"

void	malloc_fail(void)
{
	ft_print_err("malloc fail :(\n");
	exit(1);
}