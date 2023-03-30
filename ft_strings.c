#include "utils.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char) c)
			return ((char *)s);
		s++;
	}
	if (!(char) c)
		return ((char *)s);
	return (NULL);
}

int	ft_strcmp(char *s1, char *s2)
{
	unsigned char	s1_c;
	unsigned char	s2_c;

	s1_c = *s1;
	s2_c = *s2;
	while (s1_c == s2_c)
	{
		if (!s1_c || !s2_c)
			return (s1_c - s2_c);
		s1_c = *(++s1);
		s2_c = *(++s2);
	}
	return (s1_c - s2_c);
}

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

char	*ft_strdup(const char *s1)
{
	char	*res;

	res = (char *) malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!res)
		return (NULL);
	ft_strcpy(res, s1);
	return (res);
}

void	ft_strcpy(char *dst, const char *src)
{
	while (*src)
		*dst++ = *src++;
	*dst = 0;
}

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
	ret = (char *) malloc(sizeof (char) * allo_size);
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
	ret = (char *) malloc(sizeof (char) * (s1_len + s2_len + 1));
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

char	**get_args(t_list *start, t_list *last)
{
	char	**ret;
	t_list	*tmp;
	int		size;
	int		idx;

	size = 1;
	tmp = start;
	while (tmp != last)
	{
		tmp = tmp->next;
		size++;
	}
	ret = (char **) malloc(sizeof(char *) * (size + 1));
	if (!ret)
		exit(0);
	ret[size] = NULL;
	idx = 0;
	while (idx < size)
	{
		ret[idx] = ft_strdup(start->line);
		if (!ret[idx++])
			exit(0);
		start = start->next;
	}
	return (ret);
}

