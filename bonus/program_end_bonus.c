/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_end_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:31:45 by yecnam            #+#    #+#             */
/*   Updated: 2023/04/18 18:44:36 by yecnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	program_end(struct termios old_term)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &old_term);
	write(1, "bye :)\n", 7);
	exit(0);
}
