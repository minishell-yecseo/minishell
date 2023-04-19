/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:31:49 by saseo             #+#    #+#             */
/*   Updated: 2023/04/19 13:54:40 by yecnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

t_tree	*init_tree(void)
{
	t_tree	*tree;

	tree = (t_tree *)ft_calloc(1, sizeof(t_tree));
	if (!tree)
		exit(0);
	tree->root = NULL;
	tree->size = 0;
	return (tree);
}

t_node	*create_node(t_token type)
{
	t_node	*node;

	node = (t_node *)ft_calloc(1, sizeof(t_node));
	if (!node)
		exit(0);
	node->type = type;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

void	insert_left(t_node *parent, t_node *child)
{
	parent->left = child;
}

void	insert_right(t_node *parent, t_node *child)
{
	parent->right = child;
}
