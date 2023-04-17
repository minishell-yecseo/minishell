#include "minishell.h"

void	ft_dup2(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
		func_err("dup2");
}

void	ft_close(int fd)
{
	if (close(fd) == -1)
		func_err("close");
}
