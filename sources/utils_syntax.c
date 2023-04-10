#include "utils.h"

void	quote_err(void)
{
	char	*msg;

	msg = "minishell: syntax error quotation pair dose not match\n";
	write(2, msg, ft_strlen(msg));
}

void	line_syn_err(char *line)
{
	char	*msg;
	char	*tmp;

	msg = "minishell: syntax error near unexpected token `";
	msg = ft_strjoin(msg, line);
	if (!msg)
		malloc_fail();
	tmp = msg;
	msg = ft_strjoin(msg, "\'\n");
	free(tmp);
	if (!msg)
		exit(0);
	g_last_exit_code = 2;
	write(2, msg, ft_strlen(msg));
	free(msg);
}

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

int	post_syntax_checker(t_list *head)
{
	if (redir_syntax_checker(head) == 0 || \
		pipe_syntax_checker(head) == 0)
		return (0);
	return (1);
}

int	redir_syntax_checker(t_list *head)
{
	int		ret;
	t_list	*tmp;

	ret = 1;
	tmp = head;
	while (tmp)
	{
		if ((tmp->type == L_REDIR && tmp->next == NULL) || \
		(tmp->type == L_REDIR && tmp->next->type != L_WORD))
		{
			ret = 0;
			break ;
		}
		tmp = tmp->next;
	}
	if (ret == 0)
		line_syn_err(tmp->line);
	return (ret);
}

int	pipe_syntax_checker(t_list *head)
{
	if (!head)
		return (1);
	if (head->type == L_PIPE)
	{
		line_syn_err("|");
		return (0);
	}
	while (head->next != NULL)
	{
		if (head->type == L_PIPE && head->next->type == L_PIPE)
		{
			line_syn_err("|");
			return (0);
		}
		head = head->next;
	}
	if (head->type == L_PIPE)
	{
		line_syn_err("|");
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
	if (!syntax)
	{
		write(2, "syntax error with parenthesis\n", 30);
		return (0);
	}
	return (1);
}

int	parenthesis_with_stack(t_stack *stack, char *line)
{
	t_stack_node	*node;
	char			quote;
	char			*tmp;

	tmp = line;
	quote = 0;
	while (*tmp)
	{
		if (!quote && *tmp == '(')
			ft_push(stack, *tmp);
		else if (!quote && *tmp == ')')
		{
			node = ft_pop(stack);
			if (!node)
				return (0);
			free(node);
		}
		else if (!quote && char_type_for_list(*tmp) == QUOTE)
			quote = *tmp;
		else if (quote && quote == *tmp)
			quote = 0;
		tmp++;
	}
	if (stack->size != 0)
		return (0);
	return (1);
}
