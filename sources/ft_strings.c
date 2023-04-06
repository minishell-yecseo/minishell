#include "ft_strings.h"

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

	if (!s1 || !s2)
		return (-1);
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
