/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:30:45 by yecnam            #+#    #+#             */
/*   Updated: 2023/04/17 16:32:40 by yecnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	only_check_built_in(char *s)
{
	if (!ft_strcmp(s, "echo"))
		return (1);
	else if (!ft_strcmp(s, "cd"))
		return (1);
	else if (!ft_strcmp(s, "pwd"))
		return (1);
	else if (!ft_strcmp(s, "export"))
		return (1);
	else if (!ft_strcmp(s, "unset"))
		return (1);
	else if (!ft_strcmp(s, "env"))
		return (1);
	else if (!ft_strcmp(s, "exit"))
		return (1);
	else
		return (0);
}

int	check_built_in(t_tree *tree, char *s, char **args, char ***envp)
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
		return (0);
	exit(out);
}
