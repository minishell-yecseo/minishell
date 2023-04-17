/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saseo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 19:22:03 by saseo             #+#    #+#             */
/*   Updated: 2023/04/17 19:22:04 by saseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **en)
{
	char	**envp;
	t_tree	*tree;
	char	*line;
	t_set	sa;			

	if (argc != 1 || argv[1] != 0)
		exit(1);
	minishell_sig_setting(&sa.sig, &sa.old_term, &sa.term);
	minishell_start_setting(&envp, en, &tree);
	while (1)
	{
		line = readline("minishell-0.1$ ");
		if (!line)
			program_end(sa.old_term);
		else if (!*line)
			free(line);
		else if (*line)
		{
			tree_start(tree, line, &envp, sa);
			sigaction(SIGINT, &sa.sig, 0);
			sigaction(SIGQUIT, &sa.sig, 0);
		}
	}
	return (0);
}