#include "minishell.h"

int	check_char(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	check_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (check_is_path(envp[i]))
			return (1);
		i++;
	}
	return (0);
}

int	check_is_path(char *s)
{
	if (s[0] != 'P')
		return (0);
	if (s[1] != 'A')
		return (0);
	if (s[2] != 'T')
		return (0);
	if (s[3] != 'H')
		return (0);
	if (s[4] != '=')
		return (0);
	if (s[5] == 0)
		return (0);
	return (1);
}

char	*path_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		len1;
	int		len2;
	int		i;

	i = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (len1 + len2 + 2));
	if (!str)
		return (0);
	while (i < len1)
	{
		str[i] = s1[i];
		i++;
	}
	str[i++] = '/';
	while (i < len1 + len2 + 1)
	{
		str[i] = s2[i - len1 - 1];
		i++;
	}
	str[i] = '\0';
	return (str);
}
