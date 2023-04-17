/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:33:53 by yecnam            #+#    #+#             */
/*   Updated: 2023/04/17 16:33:54 by yecnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_stack	*stack_init(void)
{
	t_stack	*ret;

	ret = (t_stack *) ft_calloc(1, sizeof(t_stack));
	if (!ret)
		return (NULL);
	return (ret);
}
