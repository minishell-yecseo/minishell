#include "utils.h"

// set_pipe 직전, root에 pipe node가 있음.
void	set_pipe(t_node *parent, t_list *start, t_list *last)
{
	t_list	*tmp;
	t_list	*lst_pipe;
	t_node	*node;

	if (start == NULL)
		return ;
	lst_pipe = start;
	//while (lst_pipe->next != NULL && lst_pipe->next->type != L_PIPE)
	//	lst_pipe = lst_pipe->next;
	while (lst_pipe->type != L_PIPE && lst_pipe->next != NULL)
		lst_pipe = lst_pipe->next;
	// 왼쪽 node에 CMD type node 만들어서 삽입
	set_cmd(parent, start, lst_pipe);
	// 오른쪽에 PIPE type node 만들어서 삽입
	tmp = lst_pipe;
	while (tmp->type != L_PIPE && tmp->next != NULL)
		tmp = tmp->next;
	node = create_node(PIPE);
	insert_right(parent, node);
	// 다시 set_pipe()
	set_pipe(node, lst_pipe->next, last);
}

void	set_cmd(t_node *parent, t_list *start, t_list *last)
{
	t_node	*node;

	node = create_node(CMD);
	insert_left(parent, node);
	set_redir(node, start, last);
	set_simple_cmd(node, start, last);
}

void	set_redir(t_node *parent, t_list *start, t_list *last)
{
	t_node	*node;
	t_list	*tmp;

	if (start == NULL || start->type == L_PIPE)
		return ;
	tmp = start;
	while (tmp->type != L_REDIR && tmp != last)
		tmp = tmp->next;
	if (tmp->type != L_REDIR)
		return ;//범위를 다 훑었는데 redir 타입이 없을 경우 그냥 종료
	node = create_node(REDIR);
	if (ft_strcmp(tmp->line, "<") == 0)
		node->cont.redir_type = IN;
	else if (ft_strcmp(tmp->line, "<<") == 0)
		node->cont.redir_type = HERE_DOC;
	else if (ft_strcmp(tmp->line, ">") == 0)
		node->cont.redir_type = OUT_T;
	else if (ft_strcmp(tmp->line, ">>") == 0)
		node->cont.redir_type = OUT_A;
	node->cont.file_name = tmp->next->line;
	insert_left(parent, node);
	set_redir(node, tmp->next->next, last);
}

void	set_simple_cmd(t_node *parent, t_list *start, t_list *last)
{
	t_node	*node;
	t_list	*word_end;
	int		range_size;
	int		redir_num;

	range_size = get_list_range_size(start, last);
	redir_num = get_redir_num_in_range(start, last);
	if (redir_num * 2 == range_size)
		node = create_node(NO_CMD);
	else
	{
		start = get_word_start_list(start, last, redir_num);
		word_end = get_word_end_list(start, last);
		node = create_node(SIMPLE_CMD);
		node->cont.args = get_args(start, word_end);
		node->cont.path = start->line;
	}
	insert_right(parent, node);
}

t_list	*get_word_start_list(t_list *start, t_list *last, int redir_num)
{
	t_list	*tmp;

	tmp = start;
	if (redir_num == 0)
		return (start);
	while (tmp != last)
	{
		if (tmp->type == L_WORD)
		{
			if (tmp->prev == NULL || tmp->prev->type == L_WORD ||\
				tmp->prev->type == L_PIPE)
				break ;
		}
		tmp = tmp->next;
	}
	return (tmp);
}

t_list	*get_word_end_list(t_list *start, t_list *last)
{
	t_list	*end;

	end = start;
	while (end != last)
	{
		if (end->next == NULL || end->next->type == L_PIPE \
			|| end->next->type == L_REDIR)
			break ;
		end = end->next;
	}
	return (end);
}

int	get_list_range_size(t_list *start, t_list *last)
{
	int	size;

	size = 1;
	while (start != last)
	{
		start = start->next;
		size++;
	}
	if (last->type == L_PIPE)
		size--;
	return (size);
}

int	get_redir_num_in_range(t_list *start, t_list *last)
{
	int	num;

	num = 0;
	while (start != last)
	{
		if (start->type == L_REDIR)
			num++;
		start = start->next;
	}
	return (num);
}
