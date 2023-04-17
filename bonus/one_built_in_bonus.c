/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_built_in_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saseo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 19:22:18 by saseo             #+#    #+#             */
/*   Updated: 2023/04/17 19:22:19 by saseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tree.h"

int	one_exe_built_in(t_tree *tree, char *s, char **args, char ***envp)
{
	int	out;

	if (!ft_strcmp(s, "echo"))
		out = echo(args);
	else if (!ft_strcmp(s, "cd"))
		out = cd(args, envp);
	else if (!ft_strcmp(s, "pwd"))
		out = pwd();
	else if (!ft_strcmp(s, "export"))
		out = export(args, envp);
	else if (!ft_strcmp(s, "unset"))
		out = unset(args, envp);
	else if (!ft_strcmp(s, "env"))
		out = env(*envp);
	else if (!ft_strcmp(s, "exit"))
		out = ft_exit(args, tree);
	else
		return (-1);
	return (out);
}
