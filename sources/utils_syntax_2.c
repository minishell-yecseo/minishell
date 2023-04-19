/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_syntax_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:31:16 by saseo             #+#    #+#             */
/*   Updated: 2023/04/19 13:54:29 by yecnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	pre_syntax_checker(char *line)
{
	int	syntax;

	syntax = quote_pair_syntax_checker(line);
	if (!syntax)
		return (0);
	syntax = parenthesis_pair_checker(line);
	if (!syntax)
		return (0);
	return (1);
}

int	quote_pair_syntax_checker(char *line)
{
	int		type;
	char	quote;
	char	*tmp;

	quote = 0;
	tmp = line;
	while (*tmp)
	{
		type = char_type_for_list(*tmp);
		if (!quote && type == QUOTE)
			quote = *tmp;
		else if (quote && *tmp == quote)
			quote = 0;
		tmp++;
	}
	if (quote != 0)
	{
		quote_err();
		return (0);
	}
	return (1);
}

int	parenthesis_pair_checker(char *line)
{
	t_stack	*stack;
	int		syntax;

	stack = stack_init();
	if (!stack)
		exit(0);
	syntax = parenthesis_with_stack(stack, line);
	ft_free_stack(stack);
	if (syntax == 2)
		line_syn_err("(");
	else if (syntax == 3)
		line_syn_err(")");
	if (syntax != 1)
		return (0);
	return (1);
}

int	parenthesis_with_stack(t_stack *stack, char *line)
{
	t_stack_node	*node;
	char			quote;

	quote = 0;
	while (*line)
	{
		if (!quote && *line == '(')
			ft_push(stack, *line);
		else if (!quote && *line == ')')
		{
			node = ft_pop(stack);
			if (!node)
				return (3);
			free(node);
		}
		else if (!quote && char_type_for_list(*line) == QUOTE)
			quote = *line;
		else if (quote && quote == *line)
			quote = 0;
		line++;
	}
	if (stack->size != 0)
		return (2);
	return (1);
}
