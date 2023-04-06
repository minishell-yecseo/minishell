#include "minishell.h"
#include "tree.h"

int	key_cmp(char *s1, char *s2)
{
	int	i;
	int	len1;
	int	len2;

	len1 = 0;
	len2 = 0;
	if (!s1 || !s2)
		return (0);
	if (s1[0] == '\0' || s2[0] == '\0')
		return (0);
	while (s1[len1] && s1[len1] != '=')
		len1++;
	while (s2[len2] && s2[len2] != '=')
		len2++;
	i = 0;
	//printf("testA\n");
	while (i < len1 && i < len2)
	{
		if (s1[i] != s2[i])
		{
				//printf("testB\n");
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	//printf("testC\n");
	return (0);
}

char	**ordering_envp(char **envp)
{
	char	**en;
	char	*tmp;
	int		i;
	int		j;

	
	en = cp_envp(envp);
	i = 0;
	while (en[i])
	{
		j = i + 1;
		while (en[j])
		{
			if (en[j][0] == 0)
				break;
			//printf("i: %s, j: %s\n", en[i + 1], en[j + 1]);
			if (key_cmp(en[i], en[j]) > 0)
			{
				tmp = en[i];
				en[i] = en[j];
				en[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (en);
}

void	export_print_envp(char **envp)
{
	int		i;
	int		j;
	char	**ordered_envp;

	ordered_envp = ordering_envp(envp);
	i = 0;
	while (ordered_envp[i])
	{
		j = 0;
		printf("declare -x ");
		while (ordered_envp[i][j] != '=' && ordered_envp[i][j])
			printf("%c", ordered_envp[i][j++]);
		if (ordered_envp[i][j] == '=')
		{
			printf("%c", ordered_envp[i][j++]);
			printf("\"");
			while (ordered_envp[i][j])
				printf("%c", ordered_envp[i][j++]);
			printf("\"");
		}
		printf("\n");
		i++;
	}
	free_envp(&ordered_envp);
}

char	**make_big_arr(char ***envp)
{
	int		i;
	char	**en;

	i = 0;
	while ((*envp)[i])
		i++;
	en = (char **)malloc(sizeof(char *) * (i + 2));
	if (!en)
		exit(1);
	return (en);
}

char	**add_envp(char ***envp, char *str)
{
	int		i;
	int		flag;
	char	**en;

	en = make_big_arr(envp);
	i = 0;
	flag = 0;
	while ((*envp)[i])
	{
		if (ft_envpcmp((*envp)[i], str))
		{
			flag = 1;
			en[i] = ft_strdup(str);
		}
		else
			en[i] = ft_strdup((*envp)[i]);
		if (!en[i])
				exit(1);
		i++;
	}
	if (!flag)
		en[i++] = ft_strdup(str);
	en[i] = 0;
	free_envp(envp);
	return (en);
}

int	check_add_envp(char *str)
{
	int		i;

	i = 0;
	if (!ft_isalpha(str[i++]))
		return (0);
	while (str[i] != 0 && str[i] != '=')
	{
		if (!(ft_isalpha(str[i]) || ft_isdigit(str[i])))
			return (0);
		i++;
	}
	return (1);
}

int	export(char **arg, char ***envp)
{
	//printf("yes it's in export\n");
	int	i;
	int	end;

	i = 1;
	end = 0;
	if (!arg[1])
		export_print_envp(*envp);
	else
	{
		while (arg[i])
		{
			if (check_add_envp(arg[i]) == 1)
			{
				*envp = add_envp(envp, arg[i]);
				end = 0;
			}
			else
			{
				ft_print_err("export : '");
				ft_print_err(arg[i]);
				ft_print_err("': not a valid identifier\n");
				end = 1;
			}
			i++;
		}
	}
	return (end);
}

//int main(int argc, char **argv, char **en)
//{
//	char **envp;

//	envp = cp_envp(en);
//	int i = 0;
//	//while (envp[i])
//	//{
//	//	printf("%s\n", envp[i]);
//	//	i++;
//	//}
//	char *str_arr[] = {"export", "ZZZZZZZZZ=hi", "a", "a=a", "1", "SADF1!=A" ,0};
//	char *str2[] = {"unset", "ZZZZZZZZZ", "asdf=", "1", 0};
//	export(str_arr, &envp);
	
//	unset(str2, &envp);

//	char *str_arr2[] = {"export", 0};
//	export(str_arr2, &envp);
//	//i = 0;
//	// while (envp[i])
//	// {
//	// 	printf("%s\n", envp[i]);
//	// 	i++;
//	// }
//	free_envp(&envp);
//	system("leaks minishell");
//}
