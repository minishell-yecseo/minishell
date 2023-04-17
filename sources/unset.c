#include "minishell.h"
#include "tree.h"

int	ft_envpcmp(char *s1, char *s2)
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
	if (!check_char(s2, '='))
		return (2);
	return (1);
}

char	**make_big_del_arr(int i)
{
	char	**en;

	en = (char **)ft_calloc(sizeof(char *), (i + 1));
	if (!en)
		func_err("calloc");
	return (en);
}

char	**del_envp(char **envp, char *str)
{
	int		i;
	int		k;
	char	**en;

	i = 0;
	while (envp[i])
		i++;
	en = make_big_del_arr(i);
	i = 0;
	k = 0;
	while (envp[i])
	{
		if (!f_envpcmp(envp[i], str))
		{
			en[k] = ft_strdup(envp[i]);
			if (!en[k])
				exit(1);
			k++;
		}
		i++;
	}
	en[k] = 0;
	free_envp(&envp);
	return (en);
}

int	check_unset_envp(char *str)
{
	int		i;

	i = 0;
	if (!ft_isalpha(str[i++]))
		return (0);
	while (str[i])
	{
		if (!(ft_isalpha(str[i]) || ft_isdigit(str[i])))
			return (0);
		i++;
	}
	return (1);
}

int	unset(char **arg, char ***envp)
{
	int	i;
	int	end;

	end = 0;
	i = 1;
	while (arg[i])
	{
		if (check_unset_envp(arg[i]) == 1)
		{
			*envp = del_envp(*envp, arg[i]);
			end = 0;
		}
		else
		{
			ft_print_err("unset : '");
			ft_print_err(arg[i]);
			ft_print_err("': not a valid identifier\n");
			end = 1;
		}
		i++;
	}
	return (end);
}
