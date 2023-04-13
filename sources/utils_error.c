#include "utils.h"

void	malloc_fail(void)
{
	perror("malloc");
	exit(1);
}

void	ft_print_err(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(2, &str[i], 1);
		i++;
	}
}
