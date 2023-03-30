#include "utils.h"

int			get_w_len(char *s, char *delimiters);
void		set_test_list(t_list **head);

// test main function.
int	main(int argc, char **argv, char **envp)
{
	t_tree	*tree;
	t_node	*root;
	t_list	*head;

	tree = (t_tree *) malloc(sizeof(tree));
	set_test_list(&head);

	root = create_node(PIPE);
	tree->head = root;
	set_pipe(root, head, ft_lstlast(head));
	traverse(tree, root);
	return (0);
}

//		test set list codes
void	set_test_list(t_list **head)
{
	/*
	 * 이 문장을 넣은 것입니닷.
	 * <a ls -al >b <c | <d grep hello >e >f
	 *
	 * ft_lstnew(t_l_type type, char *line)
	 * => t_l_type 에는 세 종류가 있습니다.
	 *		L_PIPE, L_REDIR, L_WORD
	 */

	*head = ft_lstnew(L_REDIR, "<");
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
	ft_lstadd_back(head, ft_lstnew(L_WORD, "hello"));
	ft_lstadd_back(head, ft_lstnew(L_REDIR, ">"));
	ft_lstadd_back(head, ft_lstnew(L_WORD, "e"));
	ft_lstadd_back(head, ft_lstnew(L_REDIR, ">"));
	ft_lstadd_back(head, ft_lstnew(L_WORD, "f"));
	
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
	t_list	*l_pipe;
	t_node	*node;

	if (start == last || start == NULL)
		return ;
	l_pipe = start;
	while (l_pipe->type != L_PIPE && l_pipe->next != NULL)
		l_pipe = l_pipe->next;
	// 왼쪽 node에 CMD type node 만들어서 삽입
	set_cmd(parent, start, l_pipe);
	// 오른쪽에 PIPE type node 만들어서 삽입
	tmp = l_pipe;
	while (tmp->type != L_PIPE && tmp->next != NULL)
		tmp = tmp->next;
	if (tmp->next != last)
	{
		node = create_node(PIPE);
		insert_right(parent, node);
		//set_pipe(node, start->next, last);
	}
	// 다시 set_pipe()
	set_pipe(node, l_pipe->next, last);
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

	if (start == last || start == NULL)
		return ;
	tmp = start;
	while (tmp->type != L_REDIR)
		tmp = tmp->next;
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
	t_list	*w_end;

	while (start != last)
	{
		if ((start->type == L_WORD) && (start->prev->type == L_WORD \
										||start->prev->type == L_PIPE \
										||start->prev == NULL))
			break ;
		start = start->next;
	}
	if (start->prev->type == L_REDIR || start->prev->type == L_PIPE)
	{
		node = create_node(NO_CMD);
		insert_right(parent, node);
		return ;
	}
	w_end = start;
	while (w_end->next->type == L_WORD)
		w_end = w_end->next;
	node = create_node(SIMPLE_CMD);
	node->cont.path = NULL;
	node->cont.args = get_args(start, w_end);
	insert_right(parent, node);
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
