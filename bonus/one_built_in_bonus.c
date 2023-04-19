/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_built_in_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:31:40 by yecnam            #+#    #+#             */
/*   Updated: 2023/04/18 18:44:37 by yecnam           ###   ########.fr       */
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
