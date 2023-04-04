#include "minishell.h"
#include "tree.h"

int check_n(char *s)
{
	int	i;

	i = 0;
	if (*s != '-')
		return (0);
	i++;
	if (s[i] == 0)
		return (0);
	while(s[i])
	{
		if (s[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	echo(char **args)
{
	int	i;
	int	j;

	i = 0;
	if (check_n(args[1]))
	{
		i = 2;
		while (args[i])
		{
			j = 0;
			while (args[i][j])
			{
				if (args[i][j] == '\n')
					j++;
				else
				{
					printf("%c", args[i][j]);
					j++;
				}
			}
			i++;
		}
	}
	else
	{
		i = 1;
		while (args[i])
		{
			printf("%s", args[i]);
			if (args[i + 1])
				printf(" ");
			i++;
		}
		printf("\n");
	}
	return (0);
}

//int main()
//{
//	echo("-nnnnnan", "asdf asdasdffsdafadfs");
//}