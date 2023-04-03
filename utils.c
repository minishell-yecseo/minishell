#include "utils.h"

int			get_w_len(char *s, char *delimiters);
void		set_test_list(t_list **head);

void	set_test_list(t_list **head)
{
	/*
	 * 이 문장을 넣은 것입니닷.
	 * cat Makefile | >a |<a ls -al >b < c | <d grep Makefile >e >f | >last cat | cat
	 * 
	 * ft_lstnew(t_l_type type, char *line)
	 * => t_l_type 에는 세 종류가 있습니다.
	 *		L_PIPE, L_REDIR, L_WORD
	 */

	*head = ft_lstnew(L_PIPE, "|");
	ft_lstadd_back(head, ft_lstnew(L_WORD, "cat"));
	//ft_lstadd_back(head, ft_lstnew(L_WORD, 0));
/*	
	ft_lstadd_back(head, ft_lstnew(L_PIPE, "|"));
	ft_lstadd_back(head, ft_lstnew(L_REDIR, ">"));
	ft_lstadd_back(head, ft_lstnew(L_WORD, "a"));

	ft_lstadd_back(head, ft_lstnew(L_PIPE, "|"));
	ft_lstadd_back(head, ft_lstnew(L_REDIR, "<"));
	ft_lstadd_back(head, ft_lstnew(L_WORD, "a"));
	ft_lstadd_back(head, ft_lstnew(L_WORD, "ls"));
	ft_lstadd_back(head, ft_lstnew(L_WORD, "-al"));
	ft_lstadd_back(head, ft_lstnew(L_REDIR, ">"));
	ft_lstadd_back(head, ft_lstnew(L_WORD, "b"));
	ft_lstadd_back(head, ft_lstnew(L_REDIR, "<"));
	ft_lstadd_back(head, ft_lstnew(L_WORD, "c"));

	ft_lstadd_back(head, ft_lstnew(L_PIPE, "|"));
	ft_lstadd_back(head, ft_lstnew(L_REDIR, "<"));
	ft_lstadd_back(head, ft_lstnew(L_WORD, "d"));
	ft_lstadd_back(head, ft_lstnew(L_WORD, "grep"));
	ft_lstadd_back(head, ft_lstnew(L_WORD, "Makefile"));
	ft_lstadd_back(head, ft_lstnew(L_REDIR, ">"));
	ft_lstadd_back(head, ft_lstnew(L_WORD, "e"));
	ft_lstadd_back(head, ft_lstnew(L_REDIR, ">"));
	ft_lstadd_back(head, ft_lstnew(L_WORD, "f"));

	ft_lstadd_back(head, ft_lstnew(L_PIPE, "|"));
	ft_lstadd_back(head, ft_lstnew(L_REDIR, ">"));
	ft_lstadd_back(head, ft_lstnew(L_WORD, "last"));
	ft_lstadd_back(head, ft_lstnew(L_WORD, "cat"));

	ft_lstadd_back(head, ft_lstnew(L_PIPE, "|"));
	ft_lstadd_back(head, ft_lstnew(L_WORD, "cat"));
	*/
}

t_list	*ft_lstnew(t_l_type type, char *line)
{
	t_list	*ret;

	ret = (t_list *) malloc(sizeof (t_list));
	if (!ret)
		return (NULL);
	ret->type = type;
	ret->line = line;
	ret->prev = NULL;
	ret->next = NULL;
	return (ret);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*lstlast;

	if (new == NULL || lst == NULL)
		return ;
	lstlast = ft_lstlast(*lst);
	if (lstlast == NULL)
		*lst = new;
	else
	{
		new->prev = lstlast;
		lstlast->next = new;
	}
}

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (lst);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

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

int	add_redir(t_list **list, char *line, char **envp)
{
	t_list	*new;
	int		len;

	if (*line == '<' && *(line + 1) != '<')
		new = ft_lstnew(L_REDIR, "<");
	else if (*line == '<' && *(line + 1) == '<')
		new = ft_lstnew(L_REDIR, "<<");
	else if (*line == '>' && *(line + 1) != '>')
		new = ft_lstnew(L_REDIR, ">");
	else if (*line == '>' && *(line + 1) == '>')
		new = ft_lstnew(L_REDIR, ">>");
	if (!new)
		exit(0);
	ft_lstadd_back(list, new);
	len = ft_strlen(new->line);
	return (len);
}

int	add_pipe(t_list **list, char *line, char **envp)
{
	t_list	*new;

	new = ft_lstnew(L_PIPE, "|");
	if (!new)
		exit(0);
	ft_lstadd_back(list, new);
	return (1);
}

int	add_quotes(t_list **list, char *line, char **envp)
{
	t_list	*new;
	char	*new_line;
	char	quote_type;
	int		len;

	len = 1;
	quote_type = *line;
	line++;
	while (line[len] == quote_type || line[len] == '\0')
		len++;
	new_line = ft_substr(line, 0, len);
	if (!new_line)
		exit(0);
	new = ft_lstnew(L_WORD, new_line);
	if (!new)
		exit(0);
	ft_lstadd_back(list, new);
	return (len);
}

int	add_word(t_list **list, char *line, char **envp)
{
	t_list	*new;
	char	*new_line;
	int		len;

	len = 0;
	while (line[len])
	{
		if (line[len] == ' ' || (line[len] > 8 && line[len] < 14))
			break ;
		if (line[len] == '<' || line[len] == '>' || line[len] == '|')
			break ;
		len++;
	}
	if (len == 0)
		return (1);
	new_line = ft_substr(line, 0, len);
	if (!new_line)
		exit(0);
	new = ft_lstnew(L_WORD, new_line);
	if (!new)
		exit(0);
	ft_lstadd_back(list, new);
	return (len);
}

//Not Implemeted yet
t_tree	*get_tree(char *line)
{
	t_tree	*tree;
	t_list	*list;

	// lexer			: return list of lexical_tokens	
	// syntax checker	: return 0 if syntax has no error else -1
	// tree builder		: return pointer of tree
	//					: each level call their lower process functs recursively
	//					: 1) set_pipe
	//						1-1) set_cmd
	//							1-1-1) set_redir
	//							1-1-2) set_simple_cmd
	return (tree);
}
