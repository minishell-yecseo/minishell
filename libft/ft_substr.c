#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	int		allo_size;

	allo_size = len + 1;
	if ((unsigned int) ft_strlen(s) < start)
		allo_size = 1;
	else if (ft_strlen(s) - start < len)
		allo_size = ft_strlen(s) - start + 1;
	ret = (char *) ft_calloc(allo_size, sizeof (char));
	if (!ret)
		return (0);
	ft_strncpy(ret, s + start, allo_size);
	return (ret);
}
