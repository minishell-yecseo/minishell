/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:34:40 by yecnam            #+#    #+#             */
/*   Updated: 2023/04/17 16:34:41 by yecnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	traverse(t_tree *tree, t_node *cur, char ***envp)
{
	if (!tree)
		return (0);
	if (!cur)
		return (0);
	exe_cur(tree, cur, envp);
	traverse(tree, cur->left, envp);
	traverse(tree, cur->right, envp);
	return (0);
}
