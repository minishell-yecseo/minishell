#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*_s1;
	unsigned char	*_s2;

	_s1 = (unsigned char *) s1;
	_s2 = (unsigned char *) s2;
	while (n--)
	{
		if (*_s1 != *_s2)
			return (*_s1 - *_s2);
		_s1++;
		_s2++;
	}
	return (0);
}
