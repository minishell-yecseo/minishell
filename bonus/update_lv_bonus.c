/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_lv_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:43:56 by yecnam            #+#    #+#             */
/*   Updated: 2023/04/18 19:03:54 by yecnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_is_lv(char *s)
{
	if (s[0] != 'S')
		return (0);
	if (s[1] != 'H')
		return (0);
	if (s[2] != 'L')
		return (0);
	if (s[3] != 'V')
		return (0);
	if (s[4] != 'L')
		return (0);
	if (s[5] != '=')
		return (0);
	if (s[6] == 0)
		return (0);
	return (1);
}

char	*del_lv_char(char *s)
{
	char	*new;
	int		i;

	i = 6;
	while (s[i])
		i++;
	new = (char *)malloc(sizeof(char) * (i + 1));
	if (!new)
		func_err("malloc");
	i = 6;
	while (s[i])
	{
		new[i - 6] = s[i];
		i++;
	}
	new[i - 6] = 0;
	return (new);
}

char	*make_new_lv(int new)
{
	char	*s;
	char	*lv;

	lv = ft_itoa(new + 1);
	s = ft_strjoin("SHLVL=", lv);
	free(lv);
	return (s);
}

char	*update_lv(char **envp)
{
	char	*new_lv;
	char	*lv;
	int		new;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (check_is_lv(envp[i]))
			break ;
		i++;
	}
	if (!envp[i])
		return (strdup("SHLVL=1"));
	lv = del_lv_char(envp[i]);
	new = ft_atoi(lv);
	free(lv);
	new_lv = make_new_lv(new);
	return (new_lv);
}
