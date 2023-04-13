#include "minishell.h"
#include "utils.h"

void	print_exit_err(char *str)
{
	ft_print_err("exit: ");
	ft_print_err(str);
	ft_print_err(": numeric argument required\n");
	exit(255);
}

int	exit_atoi(char *str)
{
	int					i;
	int					pm;
	unsigned long long	sum;

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
			print_exit_err(str);
		if ((sum > 9223372036854775807 && pm == 1) || \
			(sum > 9223372036854775808ULL && pm == -1))
			print_exit_err(str);
	}
	exit((long long)sum * pm);
}

int	ft_exit(char **args)
{
	int		i;
	char	out_code;

	ft_print_err("exit\n");
	i = 0;
	while (args[i])
		i++;
	if (i == 1)
		exit (0);
	else if (i > 2)
	{
		ft_print_err("exit: too many arguments\n");
		return (1);
	}
	exit_atoi(args[1]);
	return (0);
}
