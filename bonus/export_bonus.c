/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:31:18 by yecnam            #+#    #+#             */
/*   Updated: 2023/04/17 16:33:16 by yecnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tree.h"

char	**make_big_arr(char ***envp)
{
	int		i;
	char	**en;

	i = 0;
	while ((*envp)[i])
		i++;
	en = (char **)ft_calloc(sizeof(char *), (i + 2));
	if (!en)
		func_err("calloc");
	return (en);
}

char	**add_envp(char ***envp, char *str)
{
	int		i;
	int		flag;
	int		flag2;
	char	**en;

	en = make_big_arr(envp);
	i = -1;
	flag = 0;
	while ((*envp)[++i])
	{
		flag2 = ft_envpcmp((*envp)[i], str);
		if (flag2 == 1)
			en[i] = ft_strdup(str);
		else
			en[i] = ft_strdup((*envp)[i]);
		if (flag2 == 1 || flag2 == 2)
			flag = 1;
		if (!en[i])
			func_err("malloc");
	}
	if (!flag)
		en[i++] = ft_strdup(str);
	en[i] = 0;
	free_envp(envp);
	return (en);
}

int	check_add_envp(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i++]))
		return (0);
	while (str[i] != 0 && str[i] != '=')
	{
		if (!(ft_isalpha(str[i]) || ft_isdigit(str[i])))
			return (0);
		i++;
	}
	return (1);
}

void	print_export_fail(char *s)
{
	ft_print_err("export: '");
	ft_print_err(s);
	ft_print_err("': not a valid identifier\n");
}

int	export(char **arg, char ***envp)
{
	int	i;
	int	end;

	i = 1;
	end = 0;
	if (!arg[1])
	{
		export_print_envp(*envp);
		return (end);
	}
	while (arg[i])
	{
		if (check_add_envp(arg[i]) == 1)
		{
			*envp = add_envp(envp, arg[i]);
			end = 0;
		}
		else
		{
			print_export_fail(arg[i]);
			end = 1;
		}
		i++;
	}
	return (end);
}
