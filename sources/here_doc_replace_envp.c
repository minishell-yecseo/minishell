#include "utils.h"

char	*here_doc_replace_envp(char *line, char **envp)
{
	char	*tmp;
	char	*new;
	int		len;
	char	quote;
	char	*old;

	new = ft_strdup(line);
	if (!new)
		exit(0);
	tmp = line;
	quote = 0;
	while (*tmp)
	{
		len = 1;
		if (quote != '\'' && *tmp == '$')
		{
			old = new;
			new = get_replaced_line(old, tmp, &len, envp);
			free(old);
		}
		tmp += len;
	}
	return (new);
}
