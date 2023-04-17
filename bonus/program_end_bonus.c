/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_end_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saseo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 19:22:33 by saseo             #+#    #+#             */
/*   Updated: 2023/04/17 19:22:35 by saseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	program_end(struct termios old_term)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &old_term);
	write(1, "bye :)\n", 7);
	exit(0);
}
