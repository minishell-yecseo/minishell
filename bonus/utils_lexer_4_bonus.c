/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer_4_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:30:49 by saseo             #+#    #+#             */
/*   Updated: 2023/04/18 18:44:26 by yecnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	get_quotes_len_for_list(char *line)
{
	int		len;
	char	quote_type;

	len = 1;
	quote_type = *line;
	while (line[len] != quote_type && line[len] != '\0')
		len++;
	return (len);
}

int	get_word_len_for_list(char *line)
{
	int		len;
	char	c;

	len = 0;
	while (line[len])
	{
		c = char_type_for_list(line[len]);
		if (c == WHITE_SPACE)
			break ;
		else if (c == C_REDIR)
			break ;
		else if (c == C_PIPE)
			break ;
		else if (c == QUOTE)
			break ;
		len++;
	}
	return (len);
}

void	set_word_list_end_var(t_list *word_list, char *line, int len)
{
	int	type;

	type = char_type_for_list(line[len]);
	if (type == QUOTE)
		word_list->is_end = 0;
	else
		word_list->is_end = 1;
}
