/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saseo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:30:10 by saseo             #+#    #+#             */
/*   Updated: 2023/04/17 16:30:12 by saseo            ###   ########.fr       */
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
