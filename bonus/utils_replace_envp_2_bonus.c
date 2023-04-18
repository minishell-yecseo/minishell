/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_replace_envp_2_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:31:07 by saseo             #+#    #+#             */
/*   Updated: 2023/04/18 18:44:23 by yecnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*get_value(char *key, char **envp)
{
	char	*ret;
	char	*envp_key;
	int		find_flag;

	if (!key || !envp || !*envp)
		return (get_value_with_flag(NULL, 0, 0, key));
	find_flag = 0;
	while (*envp)
	{
		envp_key = get_key_from_envp(*envp);
		if (ft_strcmp(key, envp_key) == 0)
		{
			find_flag = 1;
			break ;
		}
		free(envp_key);
		envp_key = NULL;
		envp++;
	}
	ret = get_value_with_flag(*envp, envp_key, find_flag, key);
	if (find_flag)
		free(envp_key);
	return (ret);
}

char	*get_key_from_envp(char *envp)
{
	char	*ret;
	char	*tmp;
	int		len;

	tmp = envp;
	len = 0;
	while (*tmp)
	{
		if (*tmp == '=')
			break ;
		tmp++;
		len++;
	}
	ret = ft_substr(envp, 0, len);
	if (!ret)
		malloc_fail();
	return (ret);
}

int	get_key_len(char *dolor)
{
	int	len;

	len = 0;
	dolor++;
	if (*dolor == '$')
		return (0);
	if (*dolor == '?')
		return (1);
	while (*dolor)
	{
		if (*dolor != 42 && (*dolor >= ' ' && *dolor <= 47))
			break ;
		else if (*dolor >= 58 && *dolor <= 64)
			break ;
		else if ((*dolor >= 91 && *dolor <= 94) || *dolor == 96)
			break ;
		else if (*dolor >= 123 && *dolor <= 126)
			break ;
		dolor++;
		len++;
	}
	return (len);
}

void	set_heredoc_flag(char *line, char *flag)
{
	if (!*flag && (*line == '<' && *(line + 1) == '<'))
		*flag = 1;
	else if (*flag && (*(line - 1) == '$'))
		*flag = 0;
}

void	set_quote_flag(char *line, char *flag)
{
	if (!*flag && (*line == '\'' || *line == '\"'))
		*flag = *line;
	else if (*flag && *flag == *line)
		*flag = 0;
}
