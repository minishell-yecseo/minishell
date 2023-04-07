#include "minishell.h"

void	path_exe(char **args, char ***envp)
{
	struct stat	s;

    if (stat(args[0], &s) == 0) 
	{
        if (S_ISREG(s.st_mode))
		{
			//printf("%s is a file.\n", args[0]);
			execve(args[0], args, *envp);
        }
		else if (S_ISDIR(s.st_mode))
		{
			printf("%s: is a directory\n", args[0]);
			exit(126);
        }
    }
	else
	{
        perror(args[0]);
		exit(127);
    }
}