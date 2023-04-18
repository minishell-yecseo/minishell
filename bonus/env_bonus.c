/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:31:04 by yecnam            #+#    #+#             */
/*   Updated: 2023/04/17 16:32:52 by yecnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tree.h"

int	env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (check_char(envp[i], '='))
			printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}
