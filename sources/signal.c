#include <signal.h>
#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

void	signal_handler(int sig)
{
	if (sig == SIGINT)
		;
}

void	get_signal(void)
{
	signal(SIGINT, signal_handler);
	//signal(SIGQUIT, SIG_IGN);
}