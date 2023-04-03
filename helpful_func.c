#include "minishell.h"
#include "tree.h"

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

//int	ft_strcmp(char *s1, char *s2)
//{
//	int	i;

//	i = 0;
//	while (s1[i] || s2[i])
//	{
//		if (s1[i] != s2[i])
//			return (0);
//		i++;
//	}
//	return (1);
//}

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

void	ft_print_err(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(2, &str[i], 1);
		i++;
	}
}