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

int	quote_pair_syntax_checker(char *line)
{
	int	type;
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
	if (redir_syntax_checker(head) == 0 ||\
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
		if ((tmp->type == L_REDIR && tmp->next == NULL) ||\
		(tmp->type == L_REDIR && tmp->next->type != L_WORD))
		{
			ret = 0;
			break ;
		}
		tmp = tmp->next;
	}
	if (ret == 0)
	{
		line_syn_err(tmp->line);
		free_line_list(head);
	}
	return (ret);
}

int	pipe_syntax_checker(t_list *head)
{
	if (head->type == L_PIPE)
	{
		line_syn_err("|");
		return (0);
	}
	while (head->next != NULL)
	{
		if (head->type == L_PIPE && head->next->type == L_PIPE)
		{
			line_syn_err("||");
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
