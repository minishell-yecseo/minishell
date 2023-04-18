/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exefile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:31:09 by yecnam            #+#    #+#             */
/*   Updated: 2023/04/18 15:55:28 by yecnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tree.h"

void	free_path(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}

void	find_path(t_node *cur, char **paths)
{
	int	i;

	i = 0;
	free(cur->cont.path);
	while (paths[i])
	{
		cur->cont.path = path_strjoin(paths[i], cur->cont.args[0]);
		if (!cur->cont.path)
			func_err("strjoin");
		if (access(cur->cont.path, F_OK) == 0)
			break ;
		free(cur->cont.path);
		cur->cont.path = 0;
		i++;
	}
}

char	*del_first_path(char *s)
{
	char	*new;
	int		i;

	i = 5;
	while (s[i])
		i++;
	new = (char *)malloc(sizeof(char) * (i + 1));
	if (!new)
		func_err("malloc");
	i = 5;
	while (s[i])
	{
		new[i - 5] = s[i];
		i++;
	}
	new[i] = 0;
	free(s);
	return (new);
}

int	check_exefile(t_node *cur, char **envp)
{
	int		i;
	char	**paths;

	i = 0;
	if (!*cur->cont.args[0])
		return (0);
	while (envp[i])
	{
		if (check_is_path(envp[i]))
			break ;
		i++;
	}
	paths = ft_split(envp[i], ':');
	paths[0] = del_first_path(paths[0]);
	if (!paths)
		func_err("malloc");
	i = 0;
	find_path(cur, paths);
	free_path(paths);
	if (cur->cont.path == 0)
		return (0);
	return (1);
}
