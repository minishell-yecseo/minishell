#include "minishell.h"
#include "tree.h"

int	env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (check_char(envp[i], '='))
			printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}
