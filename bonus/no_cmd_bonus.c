/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_cmd_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:31:38 by yecnam            #+#    #+#             */
/*   Updated: 2023/04/18 18:44:38 by yecnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	no_cmd(t_tree *tree)
{
	if (tree->last != 1)
	{
		ft_close(tree->fds[1]);
		ft_close(tree->fds[0]);
	}
	ft_dup2(tree->stdfds[0], 0);
	ft_dup2(tree->stdfds[1], 1);
}
