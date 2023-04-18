/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   with_err_func_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:32:18 by yecnam            #+#    #+#             */
/*   Updated: 2023/04/18 18:44:19 by yecnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_dup2(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
		func_err("dup2");
}

void	ft_close(int fd)
{
	if (close(fd) == -1)
		func_err("close");
}
