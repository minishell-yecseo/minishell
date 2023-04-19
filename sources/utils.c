/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:30:10 by saseo             #+#    #+#             */
/*   Updated: 2023/04/19 13:54:25 by yecnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_tree	*get_tree(char *line, char **envp)
{
	t_tree	*tree;
	t_list	*list;

	list = lexer(line, envp);
	if (!list)
		return (NULL);
	tree = tree_builder(list);
	free_line_list(list);
	return (tree);
}
