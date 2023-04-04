#include "minishell.h"
#include "tree.h"


int	one_exe_built_in(char *s, char **args, char ***envp)
{
	int out;

	if (!ft_strcmp(s, "echo"))
		out = echo(args);
	else if (!ft_strcmp(s, "cd"))
		out = cd(args, envp);
	else if (!ft_strcmp(s, "pwd"))
		out = pwd();
	else if (!ft_strcmp(s, "export"))
		out = export(args, envp);
	else if (!ft_strcmp(s, "unset"))
		out = unset(args, envp);
	else if (!ft_strcmp(s, "env"))
		out = env(*envp);
	else if (!ft_strcmp(s, "exit"))
		out = ft_exit(args);
	else
		return (-1);
	return (out);
}