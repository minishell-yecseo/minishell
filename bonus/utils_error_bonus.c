/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_error_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:30:25 by saseo             #+#    #+#             */
/*   Updated: 2023/04/18 18:44:27 by yecnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	malloc_fail(void)
{
	perror("malloc");
	exit(1);
}

void	ft_print_err(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(2, &str[i], 1);
		i++;
	}
}

int	dir_open_err(void)
{
	char	*msg;

	msg = "minishell: open current directory failed\n";
	write(2, msg, ft_strlen(msg));
	return (0);
}

void	quote_err(void)
{
	char	*msg;

	msg = "minishell: syntax error quotation pair dose not match\n";
	write(2, msg, ft_strlen(msg));
}

void	line_syn_err(char *line)
{
	char	*msg;
	char	*tmp;

	msg = "minishell: syntax error near unexpected token `";
	msg = ft_strjoin(msg, line);
	if (!msg)
		malloc_fail();
	tmp = msg;
	msg = ft_strjoin(msg, "\'\n");
	free(tmp);
	if (!msg)
		exit(0);
	g_last_exit_code = 258;
	write(2, msg, ft_strlen(msg));
	free(msg);
}
