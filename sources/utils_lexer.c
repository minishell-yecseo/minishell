#include "utils.h"

t_list	*lexer(char *line, char **envp)
{
	t_list	*ret;
	char	*replace_line;
	int		syntax;

	syntax = pre_syntax_checker(line);
	if (!syntax)
		return (NULL);
	replace_line = get_line_replace_envp(line, envp);
	syntax = quote_pair_syntax_checker(replace_line);
	if (!syntax)
		return (NULL);
	ret = NULL;
	set_list_from_line(&ret, replace_line);
	free(replace_line);
	build_list_with_space(ret);
	build_list_with_asterisk(&ret);
	syntax = post_syntax_checker(ret);
	if (!syntax)
	{
		free_line_list(ret);
		return (NULL);
	}
	return (ret);
}

void	set_list_from_line(t_list **head, char *line)
{
	char	*tmp;
	int		token_len;

	tmp = line;
	token_len = 0;
	while (*tmp)
	{
		if (char_type_for_list(*tmp) == C_REDIR)
			token_len = add_redir(head, tmp);
		else if (char_type_for_list(*tmp) == C_PIPE)
			token_len = add_pipe(head, tmp);
		else if (char_type_for_list(*tmp) == QUOTE)
			token_len = add_quotes(head, tmp);
		else
			token_len = add_word(head, tmp);
		tmp += token_len;
	}
}
