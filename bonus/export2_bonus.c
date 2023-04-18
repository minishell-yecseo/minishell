/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:31:22 by yecnam            #+#    #+#             */
/*   Updated: 2023/04/17 16:33:15 by yecnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tree.h"

void	free_envp(char ***envp)
{
	int	i;

	i = 0;
	while ((*envp)[i])
	{
		free((*envp)[i]);
		i++;
	}
	free(*envp);
}

int	key_cmp(char *s1, char *s2)
{
	int	i;
	int	len1;
	int	len2;

	len1 = 0;
	len2 = 0;
	if (!s1 || !s2)
		return (0);
	if (s1[0] == '\0' || s2[0] == '\0')
		return (0);
	while (s1[len1] && s1[len1] != '=')
		len1++;
	while (s2[len2] && s2[len2] != '=')
		len2++;
	i = 0;
	while (i < len1 && i < len2)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

char	**ordering_envp(char **envp)
{
	char	**en;
	char	*tmp;
	int		i;
	int		j;

	en = cp_envp(envp);
	i = 0;
	while (en[i])
	{
		j = i + 1;
		while (en[j])
		{
			if (en[j][0] == 0)
				break ;
			if (key_cmp(en[i], en[j]) > 0)
			{
				tmp = en[i];
				en[i] = en[j];
				en[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (en);
}

void	export_print_envp(char **envp)
{
	int		i;
	int		j;
	char	**ordered_envp;

	ordered_envp = ordering_envp(envp);
	i = 0;
	while (ordered_envp[i])
	{
		j = 0;
		printf("declare -x ");
		while (ordered_envp[i][j] != '=' && ordered_envp[i][j])
			printf("%c", ordered_envp[i][j++]);
		if (ordered_envp[i][j] == '=')
		{
			printf("%c", ordered_envp[i][j++]);
			printf("\"");
			while (ordered_envp[i][j])
				printf("%c", ordered_envp[i][j++]);
			printf("\"");
		}
		printf("\n");
		i++;
	}
	free_envp(&ordered_envp);
}
