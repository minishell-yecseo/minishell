#include "minishell.h"

void	func_err(char *str)
{
	perror(str);
	exit(1);
}