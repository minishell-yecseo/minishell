/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:30:57 by yecnam            #+#    #+#             */
/*   Updated: 2023/04/17 16:32:41 by yecnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tree.h"

void	update_pwd(char ***envp, char *s)
{
	char	*str;
	char	*pwd;

	str = getcwd(0, 0);
	if (!str)
		func_err("getcwd");
	pwd = ft_strjoin(s, str);
	if (!pwd)
		func_err("strjoin");
	*envp = add_envp(envp, pwd);
	free(str);
	free(pwd);
}

int	cd(char **args, char ***envp)
{
	if (!args[1])
	{
		ft_print_err("cd: please enter relative or absolute path\n");
		return (1);
	}
	if (!*args[1])
		return (0);
	update_pwd(envp, "OLDPWD=");
	if (chdir(args[1]))
	{
		ft_print_err("cd: ");
		perror(args[1]);
		return (1);
	}
	update_pwd(envp, "PWD=");
	return (0);
}

int	pwd(void)
{
	char	*str;

	str = getcwd(0, 0);
	if (!str)
	{
		perror("pwd :");
		exit(3);
	}
	printf("%s\n", str);
	free(str);
	return (0);
}
