/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tokenizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saseo <saseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:31:16 by saseo             #+#    #+#             */
/*   Updated: 2023/04/06 12:43:56 by saseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

//cat Makefile | >a |<a ls -al >b < c | <d grep Makefile >e >f | >last cat | cat

//환경변수로 대체

//test main function
/*
#include <stdio.h>
int	main(int argc, char **argv, char **envp)
{
	char	*line = "cat Makefile |$NOEXIST<a $PATH" ;
	char	*re;
	re = get_line_replace_envp(line, NULL);
	printf("%s\n->", line);
	printf("%s\n", re);
	free(re);
	return 0;
}
*/

char	*get_line_replace_envp(char *line, char **envp)
{
	char	*tmp;
	char	*new;
	int		len;
	int		single_quote;
	char	*old;

	new = ft_strdup(line);
	if (!new)
		exit(0);
	tmp = line;
	single_quote = 0;
	while (*tmp)
	{
		len = 1;
		if (!single_quote && *tmp == '$')
		{
			old = new;
			new = get_replaced_line(old, tmp, &len, envp);
			free(old);
		}
		else if (!single_quote && *tmp == '\'')
			single_quote = 1;
		else if (single_quote && *tmp == '\'')
			single_quote = 0;
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

	*len = get_key_len(dolor);
	key = ft_substr(dolor, 1, *len);
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
		return (get_value_with_flag(NULL, 0, 0));
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
	ret = get_value_with_flag(*envp, ft_strlen(envp_key), find_flag);
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

char	*get_value_with_flag(char *envp, int envp_key_len, int find)
{
	char	*ret;

	if (find)
		ret = ft_substr(envp, envp_key_len + 1, ft_strlen(envp));
	else
		ret = (char *) malloc(sizeof(char));
	if (!ret)
		exit(0);
	if (!find)
		*ret = 0;
	return (ret);
}

char	*get_line_with_value(char *line, char *dolor, char *key, char *value)
{
	char	*ret;
	char	*tmp;
	int		post_line_len;

	post_line_len = ft_strlen(line) - ft_strlen(dolor);
	ret = ft_substr(line, 0, post_line_len);
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

int	add_redir(t_list **list, char *line, char **envp)
{
	t_list	*new;
	int		len;

	if (*line == '<' && *(line + 1) != '<')
		new = ft_lstnew(L_REDIR, "<");
	else if (*line == '<' && *(line + 1) == '<')
		new = ft_lstnew(L_REDIR, "<<");
	else if (*line == '>' && *(line + 1) != '>')
		new = ft_lstnew(L_REDIR, ">");
	else if (*line == '>' && *(line + 1) == '>')
		new = ft_lstnew(L_REDIR, ">>");
	if (!new)
		exit(0);
	ft_lstadd_back(list, new);
	len = ft_strlen(new->line);
	return (len);
}

int	add_pipe(t_list **list, char *line, char **envp)
{
	t_list	*new;

	new = ft_lstnew(L_PIPE, "|");
	if (!new)
		exit(0);
	ft_lstadd_back(list, new);
	return (1);
}

int	add_quotes(t_list **list, char *line, char **envp)
{
	t_list	*new;
	char	*new_line;
	char	quote_type;
	int		len;

	len = 1;
	quote_type = *line;
	line++;
	while (line[len] == quote_type || line[len] == '\0')
		len++;
	new_line = ft_substr(line, 0, len);
	if (!new_line)
		exit(0);
	new = ft_lstnew(L_WORD, new_line);
	if (!new)
		exit(0);
	ft_lstadd_back(list, new);
	return (len);
}

int	add_word(t_list **list, char *line, char **envp)
{
	t_list	*new;
	char	*new_line;
	int		len;

	len = 0;
	while (line[len])
	{
		if (line[len] == ' ' || (line[len] > 8 && line[len] < 14))
			break ;
		if (line[len] == '<' || line[len] == '>' || line[len] == '|')
			break ;
		len++;
	}
	if (len == 0)
		return (1);
	new_line = ft_substr(line, 0, len);
	if (!new_line)
		exit(0);
	new = ft_lstnew(L_WORD, new_line);
	if (!new)
		exit(0);
	ft_lstadd_back(list, new);
	return (len);
}
