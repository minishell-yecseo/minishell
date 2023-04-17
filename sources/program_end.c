#include "minishell.h"

void	program_end(struct termios old_term)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &old_term);
	write(1, "bye :)\n", 7);
	exit(0);
}
