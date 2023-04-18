/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:31:50 by yecnam            #+#    #+#             */
/*   Updated: 2023/04/18 18:44:35 by yecnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		g_last_exit_code = 1;
		write(1, "\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ignore_sig(void)
{
	struct sigaction	sig;

	sig.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sig, 0);
	sigaction(SIGQUIT, &sig, 0);
}

void	change_sig(t_tree *tree)
{
	sigaction(SIGINT, &tree->sig, 0);
	sigaction(SIGQUIT, &tree->sig, 0);
}

void	restore_sig(void)
{
	struct sigaction	sig;

	sig.sa_handler = SIG_DFL;
	sigaction(SIGINT, &sig, 0);
	sigaction(SIGQUIT, &sig, 0);
}

void	minishell_sig_setting(struct sigaction *sig, \
		struct termios *old_term, struct termios *term)
{
	(*sig).sa_handler = signal_handler;
	sigaction(SIGINT, sig, 0);
	sigaction(SIGQUIT, sig, 0);
	tcgetattr(STDIN_FILENO, term);
	tcgetattr(STDIN_FILENO, old_term);
	(*term).c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, term);
}
