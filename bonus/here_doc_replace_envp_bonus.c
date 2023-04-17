/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_replace_envp_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saseo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 19:21:56 by saseo             #+#    #+#             */
/*   Updated: 2023/04/17 19:21:57 by saseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*here_doc_replace_envp(char *line, char **envp)
{
	char	*tmp;
	char	*new;
	int		len;
	char	quote;
	char	*old;

	new = ft_strdup(line);
	if (!new)
		func_err("strdup");
	tmp = line;
	quote = 0;
	while (*tmp)
	{
		len = 1;
		if (quote != '\'' && *tmp == '$')
		{
			old = new;
			new = get_replaced_line(old, tmp, &len, envp);
			if (!new)
				func_err("strdup");
			free(old);
		}
		tmp += len;
	}
	return (new);
}
