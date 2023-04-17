/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:31:47 by yecnam            #+#    #+#             */
/*   Updated: 2023/04/17 16:33:05 by yecnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_logo(void);

void	minishell_start_setting(char ***envp, char **en, t_tree **tree)
{
	*envp = cp_envp(en);
	unset_oldpath(envp);
	here_del();
	print_init_msg();
	*tree = NULL;
}

void	unset_oldpath(char ***envp)
{
	*envp = oldpwd_envp(envp, "OLDPWD");
}

char	**cp_envp(char **envp)
{
	int		i;
	char	**en;

	i = 0;
	while (envp[i])
		i++;
	en = (char **)malloc(sizeof(char *) * (i + 1));
	if (!en)
		func_err("malloc");
	i = 0;
	while (envp[i])
	{
		en[i] = ft_strdup(envp[i]);
		if (!en[i])
			func_err("strdup");
		i++;
	}
	en[i] = 0;
	return (en);
}

void	print_init_msg(void)
{
	char	*logo;
	char	*author1;
	char	*author2;

	logo = get_logo();
	author1 = "yecnam@student.42seoul.kr";
	author2 = "saseo@student.42seoul.kr";
	printf("\x1b[38;5;87m%s\x1b[0;m", logo);
	printf("\t\t\x1b[38;5;74m%34s\x1b[0;m", author1);
	printf("\n\t\t\x1b[38;5;74m%34s\n\n\x1b[0;m", author2);
}

static char	*get_logo(void)
{
	char	*logo;

	logo = "\
.__  __.._.._. ._.._.  ____  _   _  ____  _     _\n\
|  \\/  || ||  \\| || | (_ (_`| |_| || ===|| |__ | |__\n\
|_|\\/|_||_||_|\\__||_|.__)__)|_| |_||____||____||____|\n";
	return (logo);
}
