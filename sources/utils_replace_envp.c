#include "utils.h"

char	*get_line_replace_envp(char *line, char **envp)
{
	char	*tmp;
	char	*new;
	int		len;
	char	quote;
	char	*old;

	new = ft_strdup(line);
	if (!new)
		exit(0);
	tmp = line;
	quote = 0;
	while (*tmp)
	{
		len = 1;
		if (quote != '\'' && *tmp == '$')
		{
			old = new;
			new = get_replaced_line(old, tmp, &len, envp);
			free(old);
		}
		else if (!quote && *tmp == '\'')
			quote = '\'';
		else if (!quote && *tmp == '\"')
			quote = '\"';
		else if (quote && *tmp == quote)
			quote = 0;
		tmp += len;
	}
	return (new);
}

char	*get_replaced_line(char *line, char *dolor, int *len, char **envp)
{
	char	*ret;
	char	*tmp;
	char	*key;
	char	*value;

	*len = get_key_len(dolor) + 1;
	key = ft_substr(dolor, 1, *len - 1);
	value = get_value(key, envp);
	ret = get_line_with_value(line, dolor, key, value);
	free(key);
	free(value);
	return (ret);
}

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
		envp++;
	}
	ret = get_value_with_flag(*envp, ft_strlen(envp_key), find_flag, key);
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
		exit(0);
	return (ret);
}

char	*get_value_with_flag(char *envp, int envp_key_len, int find, char *key)
{
	char	*ret;

	if (find)
		ret = ft_substr(envp, envp_key_len + 1, ft_strlen(envp));
	else if (!find && ft_strcmp(key, "?") == 0)
		ret = ft_itoa(g_last_exit_code);
	else if (!find && ft_strcmp(key, "$") == 0)
		ret = ft_strjoin("", "");
	else
		ret = ft_strjoin("", "");
	if (!ret)
		exit(0);
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
		exit(0);
	tmp = ret;
	ret = ft_strjoin(ret, value);
	free(tmp);
	if (!ret)
		exit(0);
	tmp = ret;
	ret = ft_strjoin(tmp, dolor + ft_strlen(key) + 1);
	free(tmp);
	if (!ret)
		exit(0);
	return (ret);
}

int	get_key_len(char *dolor)
{
	int	len;

	len = 0;
	if (*dolor != '$')
		return (0);
	dolor++;
	if (*dolor == '$' || *dolor == '?')
		return (1);
	while (*dolor)
	{
		if (*dolor >= ' ' && *dolor <= 47)
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
