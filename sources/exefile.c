#include "minishell.h"
#include "tree.h"

void	free_path(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}

int check_exefile(t_node *cur, char **envp)
{
	int		i;
	char	**paths;

	i = 0;
	if (!*cur->cont.args[0])
		return (0);
	while (envp[i])
	{
		if (check_is_path(envp[i]))
			break ;
		i++;
	}
	paths = ft_split(envp[i], ':');
	if (!paths)
		exit(1);
	i = 0;
	while (paths[i])
	{
		cur->cont.path = path_strjoin(paths[i], cur->cont.args[0]);
		if (!cur->cont.path)
			exit(1);
		if (access(cur->cont.path, F_OK) == 0)
			break ;
		free(cur->cont.path);
		cur->cont.path = 0;
		i++;
	}
	free_path(paths);
	if (cur->cont.path == 0)
		return (0);
	return (1);
}

//int main(int a, char **av, char **en)
//{
//	t_node *cur;

//	cur = (t_node *)malloc(sizeof(t_node));
//	char *s[] = {"ls", "-al"};
//	cur->cont.args = s;
//	check_exefile(cur, en); 
//	printf("%s\n", cur->cont.path);
//	system("leaks minishell");
//}