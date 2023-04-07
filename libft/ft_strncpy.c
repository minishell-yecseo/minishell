#include "libft.h"

void	ft_strncpy(char *dest, const char *src, size_t len)
{
	while (--len)
		*dest++ = *src++;
	*dest = 0;
}
