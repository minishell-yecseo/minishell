#include "libft.h"

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
