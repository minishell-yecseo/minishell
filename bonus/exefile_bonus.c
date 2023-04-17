/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exefile_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saseo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 19:20:41 by saseo             #+#    #+#             */
/*   Updated: 2023/04/17 19:20:44 by saseo            ###   ########.fr       */
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
	if (!paths)
		func_err("malloc");
	find_path(cur, paths);
	free_path(paths);
	if (cur->cont.path == 0)
		return (0);
	return (1);
}
