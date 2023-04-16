#include "minishell.h"
#include "utils.h"

void	print_exit_err(char *str)
{
	ft_print_err("exit: ");
	ft_print_err(str);
	ft_print_err(": numeric argument required\n");
	exit(255);
}

int	exit_atoi(char *str, int i)
{
	int					pm;
	unsigned long long	sum;

	sum = 0;
	pm = 1;
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
	return (sum * pm);
}

void	exit_end(t_tree *tree, int end)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &tree->term);
	here_del();
	exit(end);
}

int	ft_exit(char **args, t_tree *tree)
{
	int		i;
	int		end;
	char	out_code;

	ft_print_err("exit\n");
	i = 0;
	while (args[i])
		i++;
	if (i == 1)
		exit_end(tree, 0);
	else
		end = exit_atoi(args[1], 0);
	if (i > 2)
	{
		ft_print_err("exit: too many arguments\n");
		return (1);
	}
	exit_end(tree, end);
	return (0);
}
