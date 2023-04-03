#include "minishell.h"
#include "tree.h"

int	cd(char **args, char ***envp)
{
	char *old_pwd;

	if (chdir(args[1]))
	{
		perror(args[1]);
		return (1);
	}
	//add_envp(envp, )
	return (0);
}

int	pwd(void)
{
	char *str;

	str = getcwd(0, 0);
	if (!str)
	{
		perror("pwd :");
		exit(3);
	}
	printf("%s\n", str);
	free(str);
	return (0);
}


// int main()
// {
// 	char *a[] = {"cd", "tdest", 0};
// 	cd(a, 0);
// 	pwd();
// }