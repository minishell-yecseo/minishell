#include "ft_strings.h"

char	*ft_strstr(char *str, char *to_find)
{
	int		space;

	space = 0;
	if (!*to_find)
		return (str);
	while (*str)
	{
		while (to_find[space])
		{
			if (str[space] != to_find[space])
			{
				space = 0;
				break ;
			}
			space++;
			if (!to_find[space])
				return (str);
		}
		str++;
	}
	return (0);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	int		allo_size;

	allo_size = len + 1;
	if ((unsigned int) ft_strlen(s) < start)
		allo_size = 1;
	else if (ft_strlen(s) - start < len)
		allo_size = ft_strlen(s) - start + 1;
	ret = (char *) ft_calloc(sizeof (char) * allo_size);
	if (!ret)
		return (0);
	ft_strncpy(ret, s + start, allo_size);
	return (ret);
}

void	ft_strncpy(char *dest, const char *src, size_t len)
{
	while (--len)
		*dest++ = *src++;
	*dest = 0;
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	int		s1_len;
	int		s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	ret = (char *) ft_calloc(sizeof (char) * (s1_len + s2_len + 1));
	if (!ret)
		return (0);
	ft_strlcpy(ret, s1, s1_len + 1);
	ft_strlcpy(ret + s1_len, s2, s1_len + s2_len + 1);
	return (ret);
}

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
