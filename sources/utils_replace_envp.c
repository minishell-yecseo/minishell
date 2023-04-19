/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_replace_envp.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:31:03 by saseo             #+#    #+#             */
/*   Updated: 2023/04/19 13:54:30 by yecnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*get_line_replace_envp(char *line, char **envp)
{
	char	*ret;
	int		len;
	char	quote;
	char	heredoc;

	ret = ft_strdup(line);
	if (!ret)
		malloc_fail();
	quote = 0;
	heredoc = 0;
	while (*line)
	{
		len = 1;
		set_quote_flag(line, &quote);
		set_heredoc_flag(line, &heredoc);
		if (quote != '\'' && !heredoc && *line == '$')
			ret = free_and_replace_line(ret, line, &len, envp);
		line += len;
	}
	return (ret);
}

char	*free_and_replace_line(char *old, char *line, int *len, char **envp)
{
	char	*new_line;

	new_line = get_replaced_line(old, line, len, envp);
	if (new_line == NULL)
		return (old);
	free(old);
	return (new_line);
}

char	*get_replaced_line(char *line, char *dolor, int *len, char **envp)
{
	char	*ret;
	char	*key;
	char	*value;

	if (get_key_len(dolor) == 0)
		return (NULL);
	*len = get_key_len(dolor) + 1;
	key = ft_substr(dolor, 1, *len - 1);
	value = get_value(key, envp);
	ret = get_line_with_value(line, dolor, key, value);
	free(key);
	free(value);
	return (ret);
}

char	*get_value_with_flag(char *envp, char *envp_key, int find, char *key)
{
	char	*ret;

	if (find)
		ret = ft_substr(envp, ft_strlen(envp_key) + 1, ft_strlen(envp));
	else if (!find && ft_strcmp(key, "?") == 0)
		ret = ft_itoa(g_last_exit_code);
	else if (!find && ft_strcmp(key, "$") == 0)
		ret = ft_strjoin("", "");
	else
		ret = ft_strjoin("", "");
	if (!ret)
		malloc_fail();
	return (ret);
}

char	*get_line_with_value(char *line, char *dolor, char *key, char *value)
{
	char	*ret;
	char	*tmp;
	int		pre_line_len;

	pre_line_len = ft_strlen(line) - ft_strlen(dolor);
	ret = ft_substr(line, 0, pre_line_len);
	if (!ret)
		malloc_fail();
	tmp = ret;
	ret = ft_strjoin(ret, value);
	free(tmp);
	if (value && !ret)
		malloc_fail();
	tmp = ret;
	ret = ft_strjoin(tmp, dolor + ft_strlen(key) + 1);
	free(tmp);
	if (!ret)
		malloc_fail();
	return (ret);
}
