#include "libft.h"

int	ft_strlen(const char *s)
{
	int	res;

	res = 0;
	if (!s || !*s)
		return (0);
	while (*s++)
		res++;
	return (res);
}
