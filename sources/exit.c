#include "minishell.h"
#include "utils.h"

int	exit_atoi(char *str)
{
	int			i;
	long long	pm;
	long long	sum;

	sum = 0;
	pm = 1;
	i = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			pm = -1;
		i++;
	}
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			sum = sum * 10 + str[i] - 48;
			i++;
		}
		else
		{
			ft_print_err("exit: ");
			ft_print_err(str);
			ft_print_err(": numeric argument required\n");
			exit(255);
		}
	}
	exit(sum * pm);
}

int ft_exit(char **args)
{
	int		i;
	char	out_code;

	ft_print_err("exit\n");
	i = 0;
	while (args[i])
		i++;
	if (i == 1)
	{
		return (0);
	}
	else if (i > 2)
	{
		ft_print_err("exit: too many arguments\n");
		return (1);
	}
	exit_atoi(args[1]);
	return (0);
}

//int main()
//{
//	char *args[] = {"exit", 0, 0};
//	ft_exit(args);
//}