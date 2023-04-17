/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_replace_envp.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:31:31 by yecnam            #+#    #+#             */
/*   Updated: 2023/04/17 16:33:12 by yecnam           ###   ########.fr       */
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
