#include "minishell.h"
#include "tree.h"

int	ft_isalpha(int c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	else if (c >= 'A' && c <= 'Z')
		return (1);
	else
		return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

//char	*ft_strdup(const char *s1)
//{
//	char	*s;
//	int		i;

//	i = 0;
//	while (s1[i])
//		i++;
//	s = (char *)malloc(sizeof(char) * (i + 1));
//	if (!s)
//		return (0);
//	s[i--] = 0;
//	while (i != -1)
//	{
//		s[i] = s1[i];
//		i--;
//	}
//	return (s);
//}
