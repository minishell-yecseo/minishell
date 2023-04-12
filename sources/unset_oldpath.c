#include "minishell.h"
#include "tree.h"

int	f_envpcmp(char *s1, char *s2)
{
	int	i;
	int	len1;
	int	len2;

	i = 0;
	len1 = 0;
	len2 = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[len1] && s1[len1] != '=')
		len1++;
	while (s2[len2] && s2[len2] != '=')
		len2++;
	if (len1 != len2)
		return (0);
	while (i < len1)
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

char	**oldpwd_envp(char ***envp, char *str)
{
	int		i;
	int		flag;
	char	**en;

	en = make_big_arr(envp);
	i = 0;
	flag = 0;
	while ((*envp)[i])
	{
		if (f_envpcmp((*envp)[i], str))
		{
			flag = 1;
			en[i] = ft_strdup(str);
		}
		else
			en[i] = ft_strdup((*envp)[i]);
		if (!en[i])
			exit(1);
		i++;
	}
	if (!flag)
		en[i++] = ft_strdup(str);
	en[i] = 0;
	free_envp(envp);
	return (en);
}
