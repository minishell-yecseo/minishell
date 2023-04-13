#include "utils.h"

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
