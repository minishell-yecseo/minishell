#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*res;

	res = (char *) ft_calloc(1, sizeof(char) * (ft_strlen(s1) + 1));
	if (!res)
		return (NULL);
	ft_strcpy(res, s1);
	return (res);
}
