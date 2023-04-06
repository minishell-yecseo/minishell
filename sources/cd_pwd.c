#include "minishell.h"
#include "tree.h"

int	cd(char **args, char ***envp)
{
	char	*pwd;
	char	*str;

	str = getcwd(0, 0);
	if (!str)
	{
		perror(args[0]);
		exit(3);
	}
	pwd = ft_strjoin("OLDPWD=", str);
	*envp = add_envp(envp, pwd);
	free(str);
	free(pwd);
	
	
	if (chdir(args[1]))
	{
		ft_print_err("cd: ");
		perror(args[1]);
		return (1);
	}


	str = getcwd(0, 0);
	if (!str)
	{
		perror(args[0]);
		exit(3);
	}

	pwd = ft_strjoin("PWD=", str);
	*envp = add_envp(envp, pwd);
	free(str);
	free(pwd);
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