/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:31:42 by yecnam            #+#    #+#             */
/*   Updated: 2023/04/17 19:07:55 by saseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	path_exe(char **args, char ***envp)
{
	struct stat	s;

	if (stat(args[0], &s) == 0)
	{
		if (S_ISREG(s.st_mode))
			execve(args[0], args, *envp);
		else if (S_ISDIR(s.st_mode))
		{
			printf("%s: is a directory\n", args[0]);
			exit(126);
		}
	}
	else
	{
		perror(args[0]);
		exit(127);
	}
}
