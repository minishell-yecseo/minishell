#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize)
{
	size_t	src_cnt;
	size_t	src_len;

	src_cnt = 0;
	src_len = ft_strlen(src);
	if (!dest || !src)
		return (-1);
	if (!dstsize)
		return (src_len);
	while (*src && (1 + src_cnt++ < dstsize))
		*dest++ = *src++;
	*dest = 0;
	return (src_len);
}
