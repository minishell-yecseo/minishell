#include "utils.h"

	/*
	 * error list
	 *	1. PIPE type이 맨 앞, 맨 뒤에 나오는 경우//post
	 *	2. PIPE type 바로 다음에 PIPE type이 나오는 경우//post
	 *	3. 따옴표 쌍이 맞지 않는 경우// in (list build 시, 환경변수 대체 완료 후 검사)
	 *	4. REDIR type 다음에 WORD타입이 바로 나오지 않는 경우//post
	 */

void	line_syn_err(char *line)
{
	char	*msg;
	char	*tmp;

	msg = "minishell: syntax error near unexpected token `";
	msg = ft_strjoin(msg, line);
	if (!msg)
		exit(0);
	tmp = msg;
	msg = ft_strjoin(msg, "\'\n");
	free(tmp);
	if (!msg)
		exit(0);
	g_last_exit_code = 2;
	write(2, msg, ft_strlen(msg));
	free(msg);
}

int	pre_syntax_checker(t_list *head)
{
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
		line_syn_err(tmp->line);//need to implement
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