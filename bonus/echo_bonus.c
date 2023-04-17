/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saseo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 19:20:15 by saseo             #+#    #+#             */
/*   Updated: 2023/04/17 19:20:17 by saseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tree.h"

int	check_n(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (*s != '-')
		return (0);
	i++;
	if (s[i] == 0)
		return (0);
	while (s[i])
	{
		if (s[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	echo_exe(char **args, int i, int j)
{
	int	flag;

	flag = 0;
	i = 2;
	while (args[i])
	{
		if (!check_n(args[i]) && flag != 0)
		{
			flag = 1;
			j = 0;
			while (args[i][j])
			{
				if (args[i][j] == '\n')
					j++;
				else
				{
					printf("%c", args[i][j]);
					j++;
				}
			}
			if (args[i + 1])
				printf(" ");
		}
		i++;
	}
}

int	echo(char **args)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (check_n(args[1]))
		echo_exe(args, i, j);
	else
	{
		i = 1;
		while (args[i])
		{
			printf("%s", args[i]);
			if (args[i + 1])
				printf(" ");
			i++;
		}
		printf("\n");
	}
	return (0);
}