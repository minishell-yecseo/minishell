#include "minishell.h"

void	signal_handler(int sig)
{
	if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ignore_handler(int sig)
{
	return ;
}

void	ignore_sig(void)
{
	struct sigaction	sig;

	sig.sa_handler = ignore_handler;
	sigaction(SIGINT, &sig, 0);
	sigaction(SIGQUIT, &sig, 0);
}

void	change_sig(t_tree *tree)
{
	sigaction(SIGINT, &tree->sig, 0);
	sigaction(SIGQUIT, &tree->sig, 0);
}

void	restore_sig(t_tree *tree)
{
	sigaction(SIGINT, &tree->old, 0);
	sigaction(SIGQUIT, &tree->old, 0);
}

void	minishell_sig_setting(struct sigaction *old_sig, struct sigaction *sig, struct termios *old_term, struct termios *term)
{
	(*sig).sa_handler = signal_handler;
	sigaction(SIGINT, sig, old_sig);
	sigaction(SIGQUIT, sig, old_sig);

	tcgetattr(STDIN_FILENO, term);
	tcgetattr(STDIN_FILENO, old_term);
	(*term).c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, term);
}